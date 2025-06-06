/**
 * @file Camera.cpp
 * @brief Implementation of the Camera class, which represents a camera actor in the scene.
 */

#include "Camera.h"

#include "Debug/Log.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

/**
 * @brief Constructs a Camera object and initializes its properties.
 */
Camera::Camera() : Actor()
{
    mClassName = "Camera";
    mName = "WorldCamera";
    SetLocation(Vec3(0, 0, 0));
    SetRotation(Quaternion::Identity);
}

/**
 * @brief Updates the camera's view matrix and other properties.
 * Calculates the forward direction and sets the view matrix in the active scene's renderer.
 */
void Camera::Update()
{
    Actor::Update();
    Vec3 forward = GetTransform().Forward();
    Vec3 target = GetLocation() + forward * 100.0f;
    Matrix4Row view = Matrix4Row::CreateLookAt(GetLocation(), target, GetTransform().Up());
    Scene::ActiveScene->GetRenderer().SetViewMatrix(view);
}

/**
 * @brief Updates the camera-specific logic. Called during the actor update cycle.
 */
void Camera::UpdateActor()
{
    Actor::UpdateActor();
}

/**
 * @brief Called when the camera is started. Used for initialization.
 */
void Camera::Start()
{
}
