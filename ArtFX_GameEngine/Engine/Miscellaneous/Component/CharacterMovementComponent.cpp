#include "CharacterMovementComponent.h"

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
    mOwner->GetTransform().position += mWalkDirection * mWalkSpeed * Time::deltaTime;
    mOwner->GetTransform().ComputeWorldTransform();
    mWalkSpeed *= (1.0f - Time::deltaTime * mLinearDamping);
}

void CharacterMovementComponent::OnEnd()
{
    Component::OnEnd();
}

void CharacterMovementComponent::Move(float pIntensity, Vec3 pDirection)
{
    mWalkDirection = pDirection;
    mWalkSpeed = mWalkSpeed * pIntensity;
}

void CharacterMovementComponent::Jump()
{
}
