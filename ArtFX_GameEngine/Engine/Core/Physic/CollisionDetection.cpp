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
    PolyCollisionComponent* aPolyComponent = dynamic_cast<PolyCollisionComponent*>(a->GetCollisionComponent());
    PolyCollisionComponent* bPolyComponent = dynamic_cast<PolyCollisionComponent*>(b->GetCollisionComponent());
    
    Box aBox = aPolyComponent->GetBoundingBox();
    Box bBox = bPolyComponent->GetBoundingBox();

    if (aBox.max.x < bBox.min.x || aBox.min.x > bBox.max.x ||
        aBox.max.y < bBox.min.y || aBox.min.y > bBox.max.y ||
        aBox.max.z < bBox.min.z || aBox.min.z > bBox.max.z) {
        return false;
        }
    
    auto aVerts = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    auto bVerts = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    std::vector<Vec3> axesToTest;
    for (size_t i = 0; i + 2 < aVerts.size(); i += 3) {
        Vec3 normal = Vec3::Normalize(Vec3::Cross(aVerts[i + 1] - aVerts[i], aVerts[i + 2] - aVerts[i]));
        axesToTest.push_back(normal);
    }
    for (size_t i = 0; i + 2 < bVerts.size(); i += 3) {
        Vec3 normal = Vec3::Normalize(Vec3::Cross(bVerts[i + 1] - bVerts[i], bVerts[i + 2] - bVerts[i]));
        axesToTest.push_back(normal);
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axesToTest) {
        float overlap;
        if (!OverlapOnAxis(aVerts, bVerts, axis, overlap)) {
            return false;
        }
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    Contact contact;
    contact.a = a;
    contact.b = b;
    contact.normal = collisionNormal;
    contact.depth = minOverlap;
    contact.start = a->GetLocation() + collisionNormal * (minOverlap * 0.5f);
    contact.end = b->GetLocation() - collisionNormal * (minOverlap * 0.5f);

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingBoxBox(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts)
{
    const std::vector<Vec3> aVerts = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    const std::vector<Vec3> bVerts = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    std::vector<Vec3> axes;
    
    const std::vector<Vec3>& aAxes = a->GetLocalAxes();
    const std::vector<Vec3>& bAxes = b->GetLocalAxes();

    for (const Vec3& axis : aAxes) axes.push_back(Vec3::Normalize(axis));
    for (const Vec3& axis : bAxes) axes.push_back(Vec3::Normalize(axis));
    
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

    Vec3 boxCenter = box->GetLocation();
    Vec3 sphereCenter = sphere->GetLocation();
    float sphereRadius = sphereComponent->GetRadius();
    
    std::vector<Vec3> boxAxes = box->GetLocalAxes();
    Box obb = boxComponent->GetBoundingBox();
    
    Vec3 closestPoint = boxCenter;
    Vec3 boxHalfSize = (obb.max - obb.min) * 0.5f;
    
    float projectionX = Vec3::Dot(sphereCenter - boxCenter, boxAxes[0]);
    projectionX = std::clamp(projectionX, -boxHalfSize.x, boxHalfSize.x);
    closestPoint += boxAxes[0] * projectionX;

    float projectionY = Vec3::Dot(sphereCenter - boxCenter, boxAxes[1]);
    projectionY = std::clamp(projectionY, -boxHalfSize.y, boxHalfSize.y);
    closestPoint += boxAxes[1] * projectionY;

    float projectionZ = Vec3::Dot(sphereCenter - boxCenter, boxAxes[2]);
    projectionZ = std::clamp(projectionZ, -boxHalfSize.z, boxHalfSize.z);
    closestPoint += boxAxes[2] * projectionZ;
    
    Vec3 difference = sphereCenter - closestPoint;
    float distanceSquared = difference.LengthSq();

    if (distanceSquared > sphereRadius * sphereRadius) {
        return false;
    }
    
    Contact contact;
    contact.a = box;
    contact.b = sphere;
    contact.normal = Vec3::Normalize(difference);
    contact.depth = sphereRadius - sqrtf(distanceSquared);
    contact.start = closestPoint;
    contact.end = sphereCenter - contact.normal * sphereRadius;

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingBoxPolygon(RigidbodyComponent* box, RigidbodyComponent* polygon, std::vector<Contact>& contacts)
{
    auto boxVerts = box->GetCollisionComponent()->GetVerticesInWorldSpace();
    auto polyVerts = polygon->GetCollisionComponent()->GetVerticesInWorldSpace();

    std::vector<Vec3> axes;
    for (const Vec3& axis : box->GetLocalAxes()) axes.push_back(axis);
    for (size_t i = 0; i + 2 < polyVerts.size(); i += 3) {
        Vec3 normal = Vec3::Normalize(Vec3::Cross(polyVerts[i + 1] - polyVerts[i], polyVerts[i + 2] - polyVerts[i]));
        axes.push_back(normal);
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axes) {
        float overlap;
        if (!OverlapOnAxis(boxVerts, polyVerts, axis, overlap)) return false;
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis;
        }
    }

    Contact contact;
    contact.a = box;
    contact.b = polygon;
    contact.normal = collisionNormal;
    contact.depth = minOverlap;
    contact.start = box->GetLocation() + collisionNormal * (minOverlap * 0.5f);
    contact.end = polygon->GetLocation() - collisionNormal * (minOverlap * 0.5f);

    contacts.push_back(contact);
    return true;
}

bool CollisionDetection::IsCollidingPolygonSphere(RigidbodyComponent* polygon, RigidbodyComponent* sphere,
                                                  std::vector<Contact>& contacts)
{
    // PolyCollisionComponent* polyComponent = dynamic_cast<PolyCollisionComponent*>(polygon->GetCollisionComponent());
    // SphereCollisionComponent* sphereComponent = dynamic_cast<SphereCollisionComponent*>(sphere->GetCollisionComponent());
    //
    // const std::vector<Vertex>& polyVertices = polyComponent->GetMesh()->GetVertices();
    // Vec3 sphereCenter = sphere->GetLocation();
    // float sphereRadius = sphereComponent->GetRadius();
    //
    // Matrix4 transform = polygon->GetTransform();
    // std::vector<Vec3> transformedVertices;
    // for (const Vertex& vertex : polyVertices) {
    //     transformedVertices.push_back(Vec3::Transform(vertex.position, transform));
    // }
    //
    // float minDistance = std::numeric_limits<float>::max();
    // Vec3 closestPoint;
    // Vec3 collisionNormal;
    //
    // for (size_t i = 0; i < transformedVertices.size(); i += 3) {
    //     if (i + 2 >= transformedVertices.size()) break;
    //     Vec3 v0 = transformedVertices[i];
    //     Vec3 v1 = transformedVertices[i + 1];
    //     Vec3 v2 = transformedVertices[i + 2];
    //
    //     Vec3 edge1 = v1 - v0;
    //     Vec3 edge2 = v2 - v0;
    //     Vec3 normal = Vec3::Normalize(Vec3::Cross(edge1, edge2));
    //
    //     float distance = Vec3::Dot(normal, sphereCenter - v0);
    //     Vec3 projection = sphereCenter - normal * distance;
    //     float distanceSq = distance * distance;
    //
    //     if (distanceSq < minDistance) {
    //         minDistance = distanceSq;
    //         closestPoint = projection;
    //         collisionNormal = (distance >= 0) ? normal : -normal;
    //     }
    // }
    //
    // if (minDistance <= sphereRadius * sphereRadius) {
    //     Contact contact;
    //     contact.a = polygon;
    //     contact.b = sphere;
    //     contact.normal = collisionNormal;
    //     contact.depth = sphereRadius - sqrtf(minDistance);
    //     contact.start = closestPoint;
    //     contact.end = sphereCenter - collisionNormal * sphereRadius;
    //
    //     contacts.push_back(contact);
    //     return true;
    // }
    //
    return false;
}

bool CollisionDetection::OverlapOnAxis(const std::vector<Vec3>& aVertices, const std::vector<Vec3>& bVertices, const Vec3& axis, float& overlap)
{
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
