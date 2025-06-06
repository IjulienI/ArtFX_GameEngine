/**
 * @file CharacterMovementComponent.h
 * @brief Declaration of the CharacterMovementComponent class, which handles movement and jumping for a character actor.
 */

#pragma once
#include "Core/Class/Component/Component.h"

/**
 * @class CharacterMovementComponent
 * @brief Component responsible for managing character movement and jumping mechanics.
 */
class CharacterMovementComponent : public Component
{
private:
    /**
     * @brief Current jump count of the character.
     */
    int mJumpCount = 0;

    /**
     * @brief Current walking speed of the character.
     */
    Vec3 mWalkSpeed = Vec3::zero;

    /**
     * @brief Flag indicating whether the character is currently moving.
     */
    bool mMoving = false;

public:
    //--Base

    /**
     * @brief Constructs a CharacterMovementComponent and initializes its properties.
     * @param pOwner Pointer to the owning Actor.
     */
    CharacterMovementComponent(Actor* pOwner);

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

    //--Public Values    

    /**
     * @brief Maximum walking speed of the character.
     */
    float mMaxWalkSpeed = 1000.0f;

    /**
     * @brief Acceleration applied when the character starts walking.
     */
    float mWalkAcceleration = 0.4f;

    /**
     * @brief Linear damping applied to reduce the character's speed over time.
     */
    float mLinearDamping = 2.0f;

    /**
     * @brief Maximum number of jumps the character can perform consecutively.
     */
    int mMaxJumpCount = 1;

    /**
     * @brief Force applied when the character jumps.
     */
    float mJumpForce = 10.0f;

    //--Public Methods

    /**
     * @brief Moves the character in a specified direction with a given intensity.
     * @param pIntensity Intensity of the movement.
     * @param pDirection Direction of the movement as a Vec3.
     */
    void Move(float pIntensity, Vec3 pDirection);

    /**
     * @brief Makes the character jump if the jump count is within the allowed limit.
     */
    void Jump();
};
