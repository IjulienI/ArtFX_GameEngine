/**
 * @file Camera.h
 * @brief Declaration of the Camera class, which represents a camera actor in the scene.
 */

#pragma once
#include "Core/Class/Actor/Actor.h"

/**
 * @class Camera
 * @brief Represents a camera in the scene, capable of updating its view matrix.
 */
class Camera : public Actor
{
public:
    /**
     * @brief Constructs a Camera object and initializes its properties.
     */
    Camera();

    /**
     * @brief Updates the camera's view matrix and other properties.
     */
    void Update() override;

    /**
     * @brief Updates the camera-specific logic. Called during the actor update cycle.
     */
    void UpdateActor() override;

    /**
     * @brief Called when the camera is started. Used for initialization.
     */
    void Start() override;
};
