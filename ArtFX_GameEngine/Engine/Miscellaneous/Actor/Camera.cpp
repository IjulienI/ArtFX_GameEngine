#include "Camera.h"

#include "Debug/Log.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

Camera::Camera():Actor()
{
    mClassName = "Camera";
    mName = "WorldCamera";
    SetLocation(Vec3(0, 0, 0));
    SetRotation(Quaternion::Identity);
}

void Camera::Update()
{
    Actor::Update();
    Vec3 forward = GetTransform().Forward();
    Vec3 target = GetLocation() + forward * 100.0f;
    Matrix4Row view = Matrix4Row::CreateLookAt(GetLocation(), target, GetTransform().Up());
    Scene::ActiveScene->GetRenderer().SetViewMatrix(view);
}

void Camera::UpdateActor()
{
    Actor::UpdateActor();
}

void Camera::Start()
{
}
