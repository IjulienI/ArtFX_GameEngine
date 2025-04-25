#include "Camera.h"

#include "Debug/Log.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

Camera::Camera():Actor()
{
    mClassName = "Camera";
    mName = "WorldCamera";
    mCameraMovement = new FpsCameraMovement(this);
    SetLocation(Vec3(0, 0, 0));
    SetRotation(Quaternion::Identity);
}

void Camera::UpdateActor()
{
    Actor::UpdateActor();
}

void Camera::Start()
{
}
