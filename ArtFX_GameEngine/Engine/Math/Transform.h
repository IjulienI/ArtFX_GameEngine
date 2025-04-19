#pragma once

#include "Matrix4Row.h"
#include "Quaternion.h"
#include "Vec3.h"
#include "Core/Class/Actor/Actor.h"

class Transform
{
private:
    bool computeWorldTransform;
    
public:
    Vec3 position;
    Vec3 scale;
    Quaternion rotation;

    Matrix4Row worldTransform;
    Actor* owner;

public:
    Transform(Actor* owner,Vec3 position, Vec3 scale, Quaternion rotation);
    Transform(Actor* owner);

    void ComputeWorldTransform();

public:
    Vec3 GetPosition();
    Vec3 GetScale();
    Quaternion GetRotation();

    Vec3 Right() const
    {
        return Vec3::Transform(Vec3::unitX, rotation);
    }

    Vec3 Up() const
    {
        return Vec3::Transform(Vec3::unitY, rotation);
    }

    Vec3 Forward() const
    {
        return Vec3::Transform(Vec3::unitZ, rotation);
    }
};
