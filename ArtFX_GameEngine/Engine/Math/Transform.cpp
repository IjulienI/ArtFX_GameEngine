#include "Transform.h"

Transform::Transform(Actor* owner, Vec3 position, Vec3 scale, Quaternion rotation) : position(position), scale(scale), rotation(rotation)
{
    computeWorldTransform = true;
}

Transform::Transform(Actor* owner) : position(Vec3::zero), scale(Vec3::one), rotation(Quaternion::Identity)
{
    computeWorldTransform = true;
}

void Transform::ComputeWorldTransform()
{
    if(!computeWorldTransform) return;
    computeWorldTransform = false;
    worldTransform = Matrix4Row::CreateScale(scale);
    worldTransform *= Matrix4Row::CreateRotationX(rotation.x);
    worldTransform *= Matrix4Row::CreateRotationY(rotation.y);
    worldTransform *= Matrix4Row::CreateRotationZ(rotation.z);
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
