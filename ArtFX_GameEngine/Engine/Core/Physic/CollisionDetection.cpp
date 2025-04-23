#include "CollisionDetection.h"

#include <algorithm>
#include <limits>

#include "PhysicConstants.h"
#include "Component/BaseCollisionComponent.h"
#include "Component/PolyCollisionComponent.h"
#include "Component/SphereCollisionComponent.h"
#include "Core/Class/Mesh/Mesh.h"

bool CollisionDetection::IsColliding(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts)
{
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
    if ((aType == CollisionType::Box && bType == CollisionType::Sphere) || 
        (aType == CollisionType::Sphere && bType == CollisionType::Box)) {
        return IsCollidingBoxSphere(a, b, contacts);
        }
    if ((aType == CollisionType::Box && bType == CollisionType::Mesh) || 
        (aType == CollisionType::Mesh && bType == CollisionType::Box)) {
        return IsCollidingBoxPolygon(a, b, contacts);
        }
    if ((aType == CollisionType::Mesh && bType == CollisionType::Sphere) || 
        (aType == CollisionType::Sphere && bType == CollisionType::Mesh)) {
        return IsCollidingPolygonSphere(a, b, contacts);
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
    
    std::vector<Vec3> aVertices = a->GetCollisionComponent()->GetVerticesInWorldSpace();
    std::vector<Vec3> bVertices = b->GetCollisionComponent()->GetVerticesInWorldSpace();

    std::vector<Vec3> aAxes = a->GetLocalAxes();
    std::vector<Vec3> bAxes = b->GetLocalAxes();
    
    std::vector<Vec3> axesToTest = aAxes;
    axesToTest.insert(axesToTest.end(), bAxes.begin(), bAxes.end());
    for (const Vec3& aAxis : aAxes) {
        for (const Vec3& bAxis : bAxes) {
            Vec3 crossProduct = Vec3::Cross(aAxis, bAxis);
            if (crossProduct.LengthSq() > EPSILON) {
                axesToTest.push_back(Vec3::Normalize(crossProduct));
            }
        }
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axesToTest) {
        float overlap;
        if (!OverlapOnAxis(aVertices, bVertices, axis, overlap)) {
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
    Box aBox = dynamic_cast<BoxCollisionComponent*>(a->GetCollisionComponent())->GetBoundingBox();
    Box bBox = dynamic_cast<BoxCollisionComponent*>(b->GetCollisionComponent())->GetBoundingBox();

    if (aBox.max.x < bBox.min.x || aBox.min.x > bBox.max.x ||
        aBox.max.y < bBox.min.y || aBox.min.y > bBox.max.y ||
        aBox.max.z < bBox.min.z || aBox.min.z > bBox.max.z) {
        return false;
        }
    
    std::vector<Vec3> aAxes = a->GetLocalAxes();
    std::vector<Vec3> bAxes = b->GetLocalAxes();

    std::vector<Vec3> axesToTest = aAxes;
    axesToTest.insert(axesToTest.end(), bAxes.begin(), bAxes.end());
    for (const Vec3& aAxis : aAxes) {
        for (const Vec3& bAxis : bAxes) {
            Vec3 crossProduct = Vec3::Cross(aAxis, bAxis);
            if (crossProduct.LengthSq() > EPSILON) {
                axesToTest.push_back(Vec3::Normalize(crossProduct));
            }
        }
    }

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;

    for (const Vec3& axis : axesToTest) {
        float overlap;
        if (!OverlapOnAxis(a, b, axis, overlap)) {
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
    BoxCollisionComponent* boxComponent = dynamic_cast<BoxCollisionComponent*>(box->GetCollisionComponent());
    PolyCollisionComponent* polyComponent = dynamic_cast<PolyCollisionComponent*>(polygon->GetCollisionComponent());

    Box boxAABB = boxComponent->GetBoundingBox();
    Box polyAABB = polyComponent->GetMesh()->GetBoundingBox();
    
    if (boxAABB.max.x < polyAABB.min.x || boxAABB.min.x > polyAABB.max.x ||
        boxAABB.max.y < polyAABB.min.y || boxAABB.min.y > polyAABB.max.y ||
        boxAABB.max.z < polyAABB.min.z || boxAABB.min.z > polyAABB.max.z) {
        return false; 
    }
    
    std::vector<Vec3> boxVertices = box->GetCollisionComponent()->GetVerticesInWorldSpace();
    std::vector<Vec3> polyVertices = polygon->GetCollisionComponent()->GetVerticesInWorldSpace();

    std::vector<Vec3> boxAxes = box->GetLocalAxes();
    std::vector<Vec3> polyAxes;
    
    for (size_t i = 0; i < polyVertices.size(); ++i) {
        Vec3 edge = polyVertices[(i + 1) % polyVertices.size()] - polyVertices[i];
        polyAxes.push_back(Vec3::Normalize(Vec3(-edge.y, edge.x, 0))); 
    }
    
    std::vector<Vec3> axesToTest = boxAxes;
    axesToTest.insert(axesToTest.end(), polyAxes.begin(), polyAxes.end());

    float minOverlap = std::numeric_limits<float>::max();
    Vec3 collisionNormal;
    
    for (const Vec3& axis : axesToTest) {
        float overlap;
        if (!OverlapOnAxis(boxVertices, polyVertices, axis, overlap)) {
            return false;
        }

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
    PolyCollisionComponent* polyComponent = dynamic_cast<PolyCollisionComponent*>(polygon->GetCollisionComponent());
    SphereCollisionComponent* sphereComponent = dynamic_cast<SphereCollisionComponent*>(sphere->GetCollisionComponent());

    const std::vector<Vertex>& polyVertices = polyComponent->GetMesh()->GetVertices();
    Vec3 sphereCenter = sphere->GetLocation();
    float sphereRadius = sphereComponent->GetRadius();

    float minDistance = std::numeric_limits<float>::max();
    Vec3 closestPoint;
    Vec3 collisionNormal;
    
    for (size_t i = 0; i < polyVertices.size(); ++i) {
        Vec3 v1 = polyVertices[i].position;
        Vec3 v2 = polyVertices[(i + 1) % polyVertices.size()].position;

        Vec3 edge = v2 - v1;
        Vec3 toSphere = sphereCenter - v1;

        float t = std::clamp(Vec3::Dot(toSphere, edge) / edge.LengthSq(), 0.0f, 1.0f);
        Vec3 projection = v1 + edge * t;

        float distanceSq = (sphereCenter - projection).LengthSq();
        if (distanceSq < minDistance) {
            minDistance = distanceSq;
            closestPoint = projection;
            collisionNormal = Vec3::Normalize(sphereCenter - projection);
        }
    }
    
    bool isInside = true;
    for (size_t i = 0; i < polyVertices.size(); ++i) {
        Vec3 v1 = polyVertices[i].position;
        Vec3 v2 = polyVertices[(i + 1) % polyVertices.size()].position;

        Vec3 edge = v2 - v1;
        Vec3 normal = Vec3::Normalize(Vec3(-edge.y, edge.x, 0));        
        if (Vec3::Dot(normal, sphereCenter - v1) > 0) {
            isInside = false;
            break;
        }
    }

    if (isInside) {
        minDistance = 0.0f;
        collisionNormal = Vec3::Normalize(sphereCenter - closestPoint);
    }
    
    if (minDistance <= sphereRadius * sphereRadius) {
        Contact contact;
        contact.a = polygon;
        contact.b = sphere;
        contact.normal = collisionNormal;
        contact.depth = sphereRadius - sqrtf(minDistance);
        contact.start = closestPoint;
        contact.end = sphereCenter - collisionNormal * sphereRadius;

        contacts.push_back(contact);
        return true;
    }

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
