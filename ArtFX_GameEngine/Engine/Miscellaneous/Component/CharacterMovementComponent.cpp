#include "CharacterMovementComponent.h"

#include "Debug/Log.h"
#include "Doom/Actors/DoomPlayer.h"
#include "Math/Time.h"

CharacterMovementComponent::CharacterMovementComponent(Actor* pOwner) : Component(pOwner)
{
    CharacterMovementComponent::OnStart();
}

void CharacterMovementComponent::OnStart()
{
    Component::OnStart();
}

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

void CharacterMovementComponent::OnEnd()
{
    Component::OnEnd();
}

void CharacterMovementComponent::Move(float pIntensity, Vec3 pDirection)
{
    mWalkSpeed = mWalkSpeed + pDirection * pIntensity * mWalkAcceleration;    
    mMoving = true;
}

void CharacterMovementComponent::Jump()
{
    
}
