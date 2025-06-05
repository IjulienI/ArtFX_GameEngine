#pragma once
#include "Math/Vec3.h"

class RigidbodyComponent;
struct Box;
class Actor;

struct HitResult
{
    bool hit = false;
    Vec3 hitPoint;
    Vec3 hitNormal;
    float distance = 0.0f;
    Actor* hitActor = nullptr;
};

class TraceSystem
{
public:
    static HitResult LineTrace(Vec3& start, Vec3& end, RigidbodyComponent* self = nullptr, bool ignoreSelf = true);

private:
    static bool RayIntersectsBox(const Vec3& rayOrigin, const Vec3& rayDir, const Box& box, float maxDist, float& outT, Vec3& outNormal);
    
};
