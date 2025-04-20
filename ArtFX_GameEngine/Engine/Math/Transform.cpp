

#include "Transform.h"

#include "Core/Class/Actor/Actor.h"

Transform::Transform(Actor* owner, Vec3 position, Vec3 scale, Quaternion rotation) : owner(owner), position(position), scale(scale), rotation(rotation)
{
    mNeedsUpdate = true;
}

Transform::Transform(Actor* owner) : owner(owner), position(Vec3::zero), scale(Vec3::one), rotation(Quaternion::Identity)
{
    mNeedsUpdate = true;
}

void Transform::ComputeWorldTransform()
{
    if(!mNeedsUpdate) return;
    mNeedsUpdate = false;
    worldTransform = Matrix4Row::CreateScale(scale);
    worldTransform *= Matrix4Row::CreateFromQuaternion(rotation);
    worldTransform *= Matrix4Row::CreateTranslation(position);
    owner->UpdateComponentsTransform();

}

Vec3 Transform::GetPosition()
{
    return position;
}

Vec3 Transform::GetScale()
{
    return scale;
}

Quaternion Transform::GetRotation()
{
    return rotation;
}

void Transform::Rotate(Vec3 pRotation)
{
    Quaternion newRotation = rotation;
    Quaternion increment;
    if(pRotation.z != 0)
    {
        increment = Quaternion(Vec3::unitZ, pRotation.z);
        newRotation = Quaternion::Concatenate(newRotation, increment);
    }
    if(pRotation.y != 0)
    {
        increment = Quaternion(Vec3::unitY, pRotation.y);
        newRotation = Quaternion::Concatenate(newRotation, increment);
    }
    if(pRotation.x != 0)
    {
        increment = Quaternion(Vec3::unitX, pRotation.x);
        newRotation = Quaternion::Concatenate(newRotation, increment);
    }
    rotation = newRotation;    
    mNeedsUpdate = true;
}

void Transform::Rotate(float pRotation, Vec3 pAxis)
{
    Quaternion increment(pAxis, pRotation);
    rotation = Quaternion::Concatenate(rotation, increment);
    mNeedsUpdate = true;
}

void Transform::RotateX(float pRotation)
{
    Quaternion newRotation = rotation;
    Quaternion increment = Quaternion(Vec3::unitZ, pRotation);
    newRotation = Quaternion::Concatenate(newRotation, increment);
    rotation = newRotation;
    mNeedsUpdate = true;
}

void Transform::RotateY(float pRotation)
{
    Quaternion newRotation = rotation;
    Quaternion increment = Quaternion(Vec3::unitX, pRotation);
    newRotation = Quaternion::Concatenate(newRotation, increment);
    rotation = newRotation;
    mNeedsUpdate = true;
}

void Transform::RotateZ(float pRotation)
{
    Quaternion newRotation = rotation;
    Quaternion increment = Quaternion(Vec3::unitY, pRotation);
    newRotation = Quaternion::Concatenate(newRotation, increment);
    rotation = newRotation;
    mNeedsUpdate = true;
}