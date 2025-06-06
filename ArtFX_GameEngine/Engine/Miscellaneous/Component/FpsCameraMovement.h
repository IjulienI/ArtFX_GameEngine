/**
 * @file FpsCameraMovement.h
 * @brief Declaration of the FpsCameraMovement class, which handles first-person camera movement and input.
 */

#pragma once
#include "Core/Class/Component/Component.h"
#include "Input/IInputListener.h"
#include "Math/Vec3.h"

class Camera;

/**
 * @class FpsCameraMovement
 * @brief Component responsible for managing first-person camera movement and input handling.
 */
class FpsCameraMovement : public Component, IInputListener
{
private:
    /**
     * @brief Pointer to the camera associated with this component.
     */
    Camera* mCamera;

    /**
     * @brief Velocity of the camera movement.
     */
    Vec3 mVelocity;

    /**
     * @brief Normal movement speed of the camera.
     */
    float mSpeed;

    /**
     * @brief Sprint movement speed of the camera.
     */
    float mSprintSpeed;

    /**
     * @brief Mouse movement delta along the X-axis.
     */
    int mMouseDeltaX;

    /**
     * @brief Mouse movement delta along the Y-axis.
     */
    int mMouseDeltaY;

    /**
     * @brief Pitch angle of the camera.
     */
    float mPitch;

    /**
     * @brief Yaw angle of the camera.
     */
    float mYaw;

    /**
     * @brief Flag indicating whether sprint mode is active.
     */
    bool mSprint;

public:
    /**
     * @brief Constructs a FpsCameraMovement component and initializes its properties.
     * @param camera Pointer to the camera actor.
     */
    FpsCameraMovement(Camera* camera);

    /**
     * @brief Called when the component is started.
     */
    void OnStart() override;

    /**
     * @brief Updates the component every frame.
     */
    void Update() override;

    /**
     * @brief Called when the component is about to be destroyed or removed.
     */
    void OnEnd() override;

    /**
     * @brief Handles input events for camera movement and actions.
     * @param event Reference to the SDL event.
     */
    void OnCall(SDL_Event& event) override;
};
