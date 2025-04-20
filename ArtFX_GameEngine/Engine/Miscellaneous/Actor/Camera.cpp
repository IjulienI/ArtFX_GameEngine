#include "Camera.h"

#include "Debug/Log.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

Camera::Camera():Actor()
{
    mCameraMovement = new FpsCameraMovement(this);
    SetLocation(Vec3(0, 0, 0));
    SetRotation(Quaternion::Identity);
}

void Camera::UpdateActor()
{
    Actor::UpdateActor();
}
