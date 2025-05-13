#include "TraceSystem.h"

#include "PhysicEngine.h"
#include "Component/BoxCollisionComponent.h"
#include "Component/RigidbodyComponent.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Class/Mesh/Mesh.h"

HitResult TraceSystem::LineTrace(Vec3& start, Vec3& end, RigidbodyComponent* self, bool ignoreSelf)
{
    HitResult result = {false, Vec3(), Vec3(), std::numeric_limits<float>::max(), nullptr};
    Vec3 dir = Vec3::Normalize(end - start);
    float maxDist = start.Distance(end);

    for (RigidbodyComponent* rigidbody : PhysicEngine::GetInstance().GetRigidbodies()) {
        if (ignoreSelf && rigidbody == self) continue;
        
        BoxCollisionComponent* col = dynamic_cast<BoxCollisionComponent*>(rigidbody->GetCollisionComponent());
        if (!col) continue;

        Box box = col->GetBoundingBox();
        Vec3 pos = rigidbody->GetOwner()->GetLocation();
        box.min += pos;
        box.max += pos;

        float t = 0.0f;
        Vec3 normal;

        if (RayIntersectsBox(start, dir, box, maxDist, t, normal)) {
            if (t < result.distance) {
                result.hit = true;
                result.distance = t;
                result.hitPoint = start + dir * t;
                result.hitNormal = normal;
                result.hitActor = rigidbody->GetOwner();
                return result;
            }
        }
    }

    return result;
}

bool TraceSystem::RayIntersectsBox(const Vec3& rayOrigin, const Vec3& rayDir, const Box& box, float maxDist,
    float& outT, Vec3& outNormal)
{
    float tMin = 0.0f;
    float tMax = maxDist;
    Vec3 normal;

    auto testAxis = [&](float start, float dir, float minB, float maxB, Vec3 axisNormal) -> bool {
        if (fabs(dir) < 1e-6f) {
            return start >= minB && start <= maxB;
        }

        float t1 = (minB - start) / dir;
        float t2 = (maxB - start) / dir;
        if (t1 > t2) {
            std::swap(t1, t2);
            axisNormal *= -1.0f;
        }

        if (t1 > tMin) {
            tMin = t1;
            normal = axisNormal;
        }

        tMax = std::min(tMax, t2);
        return tMin <= tMax;
    };

    if (!testAxis(rayOrigin.x, rayDir.x, box.min.x, box.max.x, Vec3(1, 0, 0))) return false;
    if (!testAxis(rayOrigin.y, rayDir.y, box.min.y, box.max.y, Vec3(0, 1, 0))) return false;
    if (!testAxis(rayOrigin.z, rayDir.z, box.min.z, box.max.z, Vec3(0, 0, 1))) return false;

    outT = tMin;
    outNormal = normal;
    return true;
}
