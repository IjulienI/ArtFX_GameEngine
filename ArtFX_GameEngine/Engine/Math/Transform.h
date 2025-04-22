#pragma once

#include "Matrix4Row.h"
#include "Quaternion.h"
#include "Vec3.h"

class Actor;

class Transform
{
private:
    bool mNeedsUpdate;
    
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
    Matrix4Row& GetWorldTransform()
    {
        return worldTransform;
    }

    Vec3 Right() const
    {
        return Vec3::Transform(Vec3::unitY, rotation);
    }

    Vec3 Up() const
    {
        return Vec3::Transform(Vec3::unitZ, rotation);
    }

    Vec3 Forward() const
    {
        return Vec3::Transform(Vec3::unitX, rotation);
    }

    void SetNeedsUpdate(bool needsUpdate)
    {
        mNeedsUpdate = needsUpdate;
    }

    void Rotate(Vec3 pRotation);
    void Rotate(float pRotation, Vec3 pAxis);
    void RotateX(float pRotation);
    void RotateY(float pRotation);
    void RotateZ(float pRotation);
};
