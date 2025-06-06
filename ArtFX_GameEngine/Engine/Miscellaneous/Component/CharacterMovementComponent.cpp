/**
 * @file CharacterMovementComponent.cpp
 * @brief Implementation of the CharacterMovementComponent class, which handles movement and jumping for a character actor.
 */

#include "CharacterMovementComponent.h"

#include "Debug/Log.h"
#include "Doom/Actors/DoomPlayer.h"
#include "Math/Time.h"

/**
 * @brief Constructs a CharacterMovementComponent and initializes its properties.
 * @param pOwner Pointer to the owning Actor.
 */
CharacterMovementComponent::CharacterMovementComponent(Actor* pOwner) : Component(pOwner)
{
    CharacterMovementComponent::OnStart();
}

/**
 * @brief Called when the component is started.
 */
void CharacterMovementComponent::OnStart()
{
    Component::OnStart();
}

/**
 * @brief Updates the component every frame.
 * Handles movement damping and updates the character's position based on its walking speed.
 */
void CharacterMovementComponent::Update()
{
    Component::Update();
    if (!(mWalkSpeed.Length() >= mMaxWalkSpeed))
    {
        mOwner->GetTransform().position += (mWalkSpeed) * Time::deltaTime;
    }
    mWalkSpeed *= (1.0f - Time::deltaTime * (mMoving ? mLinearDamping : mLinearDamping * 3.0f));
    if (mMoving)
    {
        mMoving = false;
    }
}

/**
 * @brief Called when the component is about to be destroyed or removed.
 */
void CharacterMovementComponent::OnEnd()
{
    Component::OnEnd();
}

/**
 * @brief Moves the character in a specified direction with a given intensity.
 * @param pIntensity Intensity of the movement.
 * @param pDirection Direction of the movement as a Vec3.
 */
void CharacterMovementComponent::Move(float pIntensity, Vec3 pDirection)
{
    mWalkSpeed = mWalkSpeed + pDirection * pIntensity * mWalkAcceleration;    
    mMoving = true;
}

/**
 * @brief Makes the character jump if the jump count is within the allowed limit.
 */
void CharacterMovementComponent::Jump()
{
    
}
