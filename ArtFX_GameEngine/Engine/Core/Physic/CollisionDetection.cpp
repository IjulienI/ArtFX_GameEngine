#include "CollisionDetection.h"

#include <algorithm>
#include <limits>

#include "PhysicConstants.h"
#include "Component/BaseCollisionComponent.h"
#include "Component/PolyCollisionComponent.h"
#include "Component/SphereCollisionComponent.h"
#include "Core/Class/Mesh/Mesh.h"
#include "Math/Matrix4.h"

bool CollisionDetection::IsColliding(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts)
{
    if (a->IsStatic() && b->IsStatic()) {
        return false;
    }
    
    CollisionType aType = a->GetCollisionComponent()->GetCollisionType();
    CollisionType bType = b->GetCollisionComponent()->GetCollisionType();


    if (aType == CollisionType::Sphere && bType == CollisionType::Sphere) {
        return IsCollidingSphereSphere(a, b, contacts);
    }

    if (aType == CollisionType::Box && bType == CollisionType::Box) {
        return IsCollidingBoxBox(a, b, contacts);
    }

    if (aType == CollisionType::Mesh && bType == CollisionType::Mesh) {
        return IsCollidingPolygonPolygon(a, b, contacts);
    }

    if (aType == CollisionType::Box && bType == CollisionType::Sphere) {
        return IsCollidingBoxSphere(a, b, contacts);
    }

    if (aType == CollisionType::Sphere && bType == CollisionType::Box) {
        return IsCollidingBoxSphere(b, a, contacts);
    }

    if (aType == CollisionType::Box && bType == CollisionType::Mesh) {
        return IsCollidingBoxPolygon(a, b, contacts);
    }

    if (aType == CollisionType::Mesh && bType == CollisionType::Box) {
        return IsCollidingBoxPolygon(b, a, contacts);
    }

    if (aType == CollisionType::Mesh && bType == CollisionType::Sphere) {
        return IsCollidingPolygonSphere(a, b, contacts);
    }

    if (aType == CollisionType::Sphere && bType == CollisionType::Mesh) {
        return IsCollidingPolygonSphere(b, a, contacts);
    }

    return false;
}

bool CollisionDetection::IsCollidingSphereSphere(RigidbodyComponent* a, RigidbodyComponent* b,
    std::vector<Contact>& contacts)
{
    SphereCollisionComponent* aSphereComponent = dynamic_cast<SphereCollisionComponent*>(a->GetCollisionComponent());
    SphereCollisionComponent* bSphereComponent = dynamic_cast<SphereCollisionComponent*>(b->GetCollisionComponent());
    
    Vec3 positionA = a->GetLocation();
    Vec3 positionB = b->GetLocation();
    float radiusA = aSphereComponent->GetRadius();
    float radiusB = bSphereComponent->GetRadius();

    Vec3 ab = positionB - positionA;
    float distanceSquared = ab.LengthSq();
    float radiusSum = radiusA + radiusB;

    if (distanceSquared > radiusSum * radiusSum) {
        return false;
    }

    Contact contact;
    contact.a = a;
    contact.b = b;
    contact.normal = Vec3::Normalize(ab);
    contact.depth = radiusSum - sqrtf(distanceSquared);
    contact.start = positionA + contact.normal * radiusA;
    contact.end = positionB - contact.normal * radiusB;

    contacts.push_back(contact);
    return true; 
}

bool CollisionDetection::IsCollidingPolygonPolygon(RigidbodyComponent* a, RigidbodyComponent* b,
    std::vector<Contact>& contacts)
{
    const std::vector<Vec3>& aVerts = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    const std::vector<Vec3>& bVerts = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    if (aVerts.empty() || bVerts.empty()) return false;

    std::vector<Vec3> aAxes, bAxes;

    for (size_t i = 0; i + 2 < aVerts.size(); i += 3) {
        Vec3 normal = Vec3::Normalize(Vec3::Cross(aVerts[i + 1] - aVerts[i], aVerts[i + 2] - aVerts[i]));
        if (normal.LengthSq() > EPSILON)
            aAxes.push_back(normal);
    }

    for (size_t i = 0; i + 2 < bVerts.size(); i += 3) {
        Vec3 normal = Vec3::Normalize(Vec3::Cross(bVerts[i + 1] - bVerts[i], bVerts[i + 2] - bVerts[i]));
        if (normal.LengthSq() > EPSILON)
            bAxes.push_back(normal);
    }

    std::vector<Vec3> axes = aAxes;
    axes.insert(axes.end(), bAxes.begin(), bAxes.end());

    for (const Vec3& axisA : aAxes) {
        for (const Vec3& axisB : bAxes) {
            Vec3 cross = Vec3::Cross(axisA, axisB);
            if (cross.LengthSq() > EPSILON) {
                axes.push_back(Vec3::Normalize(cross));
            }
        }
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axes) {
        float overlap;
        if (!OverlapOnAxis(aVerts, bVerts, axis, overlap)) {
            return false;
        }
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    Vec3 direction = b->GetLocation() - a->GetLocation();
    if (Vec3::Dot(direction, collisionNormal) < 0.0f) {
        collisionNormal = -collisionNormal;
    }
    
    std::vector<Vec3> clippedPoints;
    ComputeContactManifold(aVerts, bVerts, collisionNormal, clippedPoints);

    if (clippedPoints.empty()) return false;

    for (const Vec3& p : clippedPoints) {
        Contact contact;
        contact.a = a;
        contact.b = b;
        contact.normal = collisionNormal;
        contact.depth = minOverlap;
        contact.start = p;
        contact.end = p - collisionNormal * minOverlap;
        contacts.push_back(contact);
    }

    return true;
}

bool CollisionDetection::IsCollidingBoxBox(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts)
{    
    const std::vector<Vec3>& aVerts = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    const std::vector<Vec3>& bVerts = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    const std::vector<Vec3>& aAxes = a->GetLocalAxes();
    const std::vector<Vec3>& bAxes = b->GetLocalAxes();

    std::vector<Vec3> axes;
    axes.reserve(aAxes.size() + bAxes.size() + aAxes.size() * bAxes.size()); 
    
    axes.insert(axes.end(), aAxes.begin(), aAxes.end());
    axes.insert(axes.end(), bAxes.begin(), bAxes.end());
    
    for (const Vec3& aAxis : aAxes) {
        for (const Vec3& bAxis : bAxes) {
            Vec3 cross = Vec3::Cross(aAxis, bAxis);
            if (cross.LengthSq() > EPSILON) {
                axes.push_back(Vec3::Normalize(cross)); 
            }
        }
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;
    
    for (const Vec3& axis : axes) {
        float overlap;
        if (!OverlapOnAxis(aVerts, bVerts, axis, overlap)) {
            return false; 
        }
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }
    
    Vec3 direction = b->GetLocation() - a->GetLocation();
    if (Vec3::Dot(direction, collisionNormal) < 0.0f) {
        collisionNormal = -collisionNormal;
    }
    
    Vec3 contactPointA = a->GetLocation() + collisionNormal * (minOverlap * 0.5f);
    Vec3 contactPointB = b->GetLocation() - collisionNormal * (minOverlap * 0.5f);

    float maxProjectionA = std::numeric_limits<float>::lowest();
    for (const Vec3& vertex : aVerts) {
        float projection = Vec3::Dot(vertex, collisionNormal);
        if (projection > maxProjectionA) {
            maxProjectionA = projection;
            contactPointA = vertex;
        }
    }

    float maxProjectionB = std::numeric_limits<float>::lowest();
    for (const Vec3& vertex : bVerts) {
        float projection = Vec3::Dot(vertex, -collisionNormal);
        if (projection > maxProjectionB) {
            maxProjectionB = projection;
            contactPointB = vertex;
        }
    }
    
    Contact contact;
    contact.a = a;
    contact.b = b;
    contact.normal = collisionNormal;
    contact.depth = minOverlap;
    contact.start = contactPointA;
    contact.end = contactPointB;

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingBoxSphere(RigidbodyComponent* box, RigidbodyComponent* sphere, std::vector<Contact>& contacts)
{
    BoxCollisionComponent* boxComponent = dynamic_cast<BoxCollisionComponent*>(box->GetCollisionComponent());
    SphereCollisionComponent* sphereComponent = dynamic_cast<SphereCollisionComponent*>(sphere->GetCollisionComponent());

    Vec3 sphereCenter = sphere->GetLocation();
    float sphereRadius = sphereComponent->GetRadius();

    std::vector<Vec3> boxAxes = box->GetLocalAxes();
    Box obb = boxComponent->GetBoundingBox();
    Vec3 boxHalfSize = (obb.max - obb.min) * 0.5f;
    
    Vec3 localCenter = (obb.min + obb.max) * 0.5f;
    
    Vec3 boxWorldCenter = box->GetLocation();
    boxWorldCenter += boxAxes[0] * localCenter.x;
    boxWorldCenter += boxAxes[1] * localCenter.y;
    boxWorldCenter += boxAxes[2] * localCenter.z;
    
    Vec3 closestPoint = boxWorldCenter;
    Vec3 delta = sphereCenter - boxWorldCenter;
    
    {
        float projection = Vec3::Dot(delta, boxAxes[0]);
        float clamped = std::clamp(projection, -boxHalfSize.x, boxHalfSize.x);
        closestPoint += boxAxes[0] * clamped;
    }
    
    {
        float projection = Vec3::Dot(delta, boxAxes[1]);
        float clamped = std::clamp(projection, -boxHalfSize.y, boxHalfSize.y);
        closestPoint += boxAxes[1] * clamped;
    }
    
    {
        float projection = Vec3::Dot(delta, boxAxes[2]);
        float clamped = std::clamp(projection, -boxHalfSize.z, boxHalfSize.z);
        closestPoint += boxAxes[2] * clamped;
    }
    
    Vec3 difference = sphereCenter - closestPoint;
    float distanceSquared = difference.LengthSq();

    if (distanceSquared > sphereRadius * sphereRadius) {
        return false;
    }
    
    Contact contact;
    contact.a = box;
    contact.b = sphere;

    if (distanceSquared > EPSILON) {
        contact.normal = Vec3::Normalize(difference);
    } else {
        contact.normal = boxAxes[1];
    }

    contact.depth = sphereRadius - sqrtf(distanceSquared);
    contact.start = closestPoint;
    contact.end = sphereCenter - contact.normal * sphereRadius;

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingBoxPolygon(RigidbodyComponent* box, RigidbodyComponent* polygon, std::vector<Contact>& contacts)
{
        const std::vector<Vec3>& boxVerts = box->GetCollisionComponent()->GetVerticesInWorldSpace();
    const std::vector<Vec3>& polyVerts = polygon->GetCollisionComponent()->GetVerticesInWorldSpace();
    const std::vector<Vec3>& boxAxes = box->GetLocalAxes();

    std::vector<Vec3> axes;

    // 1. Box local axes (X, Y, Z)
    for (const Vec3& axis : boxAxes) {
        axes.push_back(Vec3::Normalize(axis));
    }

    // 2. Global average normal of the polygon
    Vec3 avgNormal = Vec3::zero;
    for (size_t i = 0; i + 2 < polyVerts.size(); i += 3) {
        avgNormal += Vec3::Cross(polyVerts[i + 1] - polyVerts[i], polyVerts[i + 2] - polyVerts[i]);
    }
    if (avgNormal.LengthSq() > EPSILON) {
        axes.push_back(Vec3::Normalize(avgNormal));
    }

    // SAT
    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axes) {
        float overlap;
        if (!OverlapOnAxis(boxVerts, polyVerts, axis, overlap))
            return false;

        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    // Correct normal direction
    Vec3 direction = polygon->GetLocation() - box->GetLocation();
    if (Vec3::Dot(direction, collisionNormal) < 0.0f) {
        collisionNormal = -collisionNormal;
    }

    // Find deepest points
    Vec3 deepestPointA;
    float maxProjA = -FLT_MAX;
    for (const Vec3& v : boxVerts) {
        float proj = Vec3::Dot(v, collisionNormal);
        if (proj > maxProjA) {
            maxProjA = proj;
            deepestPointA = v;
        }
    }

    Vec3 deepestPointB;
    float maxProjB = -FLT_MAX;
    for (const Vec3& v : polyVerts) {
        float proj = Vec3::Dot(v, -collisionNormal);
        if (proj > maxProjB) {
            maxProjB = proj;
            deepestPointB = v;
        }
    }

    // Create contact
    Contact contact;
    contact.a = box;
    contact.b = polygon;
    contact.normal = collisionNormal;
    contact.depth = minOverlap;
    contact.start = deepestPointA;
    contact.end = deepestPointB;

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingPolygonSphere(RigidbodyComponent* polygon, RigidbodyComponent* sphere,
                                                  std::vector<Contact>& contacts)
{
    //TEMP for the moment its juste Box to Sphere
    PolyCollisionComponent* boxComponent = dynamic_cast<PolyCollisionComponent*>(polygon->GetCollisionComponent());
    SphereCollisionComponent* sphereComponent = dynamic_cast<SphereCollisionComponent*>(sphere->GetCollisionComponent());

    Vec3 sphereCenter = sphere->GetLocation();
    float sphereRadius = sphereComponent->GetRadius();

    std::vector<Vec3> boxAxes = polygon->GetLocalAxes();
    Box obb = boxComponent->GetBoundingBox();
    Vec3 boxHalfSize = (obb.max - obb.min) * 0.5f;
    
    Vec3 localCenter = (obb.min + obb.max) * 0.5f;
    
    Vec3 boxWorldCenter = polygon->GetLocation();
    boxWorldCenter += boxAxes[0] * localCenter.x;
    boxWorldCenter += boxAxes[1] * localCenter.y;
    boxWorldCenter += boxAxes[2] * localCenter.z;
    
    Vec3 closestPoint = boxWorldCenter;
    Vec3 delta = sphereCenter - boxWorldCenter;
    
    {
        float projection = Vec3::Dot(delta, boxAxes[0]);
        float clamped = std::clamp(projection, -boxHalfSize.x, boxHalfSize.x);
        closestPoint += boxAxes[0] * clamped;
    }
    
    {
        float projection = Vec3::Dot(delta, boxAxes[1]);
        float clamped = std::clamp(projection, -boxHalfSize.y, boxHalfSize.y);
        closestPoint += boxAxes[1] * clamped;
    }
    
    {
        float projection = Vec3::Dot(delta, boxAxes[2]);
        float clamped = std::clamp(projection, -boxHalfSize.z, boxHalfSize.z);
        closestPoint += boxAxes[2] * clamped;
    }
    
    Vec3 difference = sphereCenter - closestPoint;
    float distanceSquared = difference.LengthSq();

    if (distanceSquared > sphereRadius * sphereRadius) {
        return false;
    }
    
    Contact contact;
    contact.a = polygon;
    contact.b = sphere;

    if (distanceSquared > EPSILON) {
        contact.normal = Vec3::Normalize(difference);
    } else {
        contact.normal = boxAxes[1];
    }

    contact.depth = sphereRadius - sqrtf(distanceSquared);
    contact.start = closestPoint;
    contact.end = sphereCenter - contact.normal * sphereRadius;

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::OverlapOnAxis(const std::vector<Vec3>& aVertices, const std::vector<Vec3>& bVertices, const Vec3& axis, float& overlap)
{
    float minBox = std::numeric_limits<float>::max();
    float maxBox = std::numeric_limits<float>::lowest();
    for (const Vec3& vertex : aVertices) {
        float projection = Vec3::Dot(vertex, axis);
        minBox = std::min(minBox, projection);
        maxBox = std::max(maxBox, projection);
    }
    
    float minPoly = std::numeric_limits<float>::max();
    float maxPoly = std::numeric_limits<float>::lowest();
    for (const Vec3& vertex : bVertices) {
        float projection = Vec3::Dot(vertex, axis);
        minPoly = std::min(minPoly, projection);
        maxPoly = std::max(maxPoly, projection);
    }
    
    if (maxBox < minPoly || maxPoly < minBox) {
        return false; 
    }
    
    overlap = std::min(maxBox, maxPoly) - std::max(minBox, minPoly);
    return true; 
}

bool CollisionDetection::OverlapOnAxis(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& axis, float& overlap)
{
    std::vector<Vec3> aVertices = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    std::vector<Vec3> bVertices = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    float aMin = std::numeric_limits<float>::max();
    float aMax = std::numeric_limits<float>::lowest();
    float bMin = std::numeric_limits<float>::max();
    float bMax = std::numeric_limits<float>::lowest();

    for (const Vec3& vertex : aVertices) {
        float projection = Vec3::Dot(vertex, axis);
        aMin = std::min(aMin, projection);
        aMax = std::max(aMax, projection);
    }

    for (const Vec3& vertex : bVertices) {
        float projection = Vec3::Dot(vertex, axis);
        bMin = std::min(bMin, projection);
        bMax = std::max(bMax, projection);
    }
    
    if (aMax < bMin || bMax < aMin) {
        return false;
    }

    overlap = std::min(aMax, bMax) - std::max(aMin, bMin);
    return true;
}

bool CollisionDetection::IsPointInTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& p)
{
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;
    Vec3 v0p = p - v0;

    float dot00 = Vec3::Dot(v0v1, v0v1);
    float dot01 = Vec3::Dot(v0v1, v0v2);
    float dot02 = Vec3::Dot(v0v1, v0p);
    float dot11 = Vec3::Dot(v0v2, v0v2);
    float dot12 = Vec3::Dot(v0v2, v0p);

    float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

void CollisionDetection::ComputeContactManifold(const std::vector<Vec3>& aVerts, const std::vector<Vec3>& bVerts, const Vec3& collisionNormal, std::vector<Vec3>& contactPoints)
{
    auto GetReferenceFace = [](const std::vector<Vec3>& verts, const Vec3& normal) -> std::vector<Vec3> {
        float minDot = FLT_MAX;
        std::vector<Vec3> bestFace;

        for (size_t i = 0; i + 2 < verts.size(); i += 3) {
            Vec3 n = Vec3::Normalize(Vec3::Cross(verts[i + 1] - verts[i], verts[i + 2] - verts[i]));
            float dot = Vec3::Dot(n, normal);
            if (dot < minDot) {
                minDot = dot;
                bestFace = { verts[i], verts[i + 1], verts[i + 2] };
            }
        }
        return bestFace;
    };

    std::vector<Vec3> refFace = GetReferenceFace(aVerts, collisionNormal);
    std::vector<Vec3> incFace = GetReferenceFace(bVerts, -collisionNormal);

    if (refFace.size() < 3 || incFace.size() < 3) return;
    
    Vec3 refNormal = Vec3::Normalize(Vec3::Cross(refFace[1] - refFace[0], refFace[2] - refFace[0]));
    float refPlaneDist = Vec3::Dot(refNormal, refFace[0]);
    
    auto ClipPolygonAgainstPlane = [](const std::vector<Vec3>& poly, const Vec3& planeNormal, float planeOffset) -> std::vector<Vec3> {
        std::vector<Vec3> output;
        for (size_t i = 0; i < poly.size(); ++i) {
            Vec3 current = poly[i];
            Vec3 next = poly[(i + 1) % poly.size()];

            float d1 = Vec3::Dot(current, planeNormal) - planeOffset;
            float d2 = Vec3::Dot(next, planeNormal) - planeOffset;

            if (d1 >= 0) output.push_back(current);
            if ((d1 >= 0) != (d2 >= 0)) {
                Vec3 edge = next - current;
                float t = d1 / (d1 - d2);
                output.push_back(current + edge * t);
            }
        }
        return output;
    };
    
    std::vector<Vec3> clipped = incFace;
    
    for (int i = 0; i < 3; ++i) {
        Vec3 v1 = refFace[i];
        Vec3 v2 = refFace[(i + 1) % 3];
        Vec3 edge = v2 - v1;
        Vec3 inwardNormal = Vec3::Normalize(Vec3::Cross(refNormal, edge));
        float offset = Vec3::Dot(inwardNormal, v1);
        clipped = ClipPolygonAgainstPlane(clipped, inwardNormal, offset);
        if (clipped.empty()) break;
    }

    for (Vec3& p : clipped) {
        float d = Vec3::Dot(refNormal, p) - refPlaneDist;
        if (d <= EPSILON) { 
            contactPoints.push_back(p - refNormal * d); 
        }
    }
}
