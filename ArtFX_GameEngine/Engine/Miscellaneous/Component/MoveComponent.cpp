#include "MoveComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Math/Maths.h"
#include "Math/Time.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder), mSpeed(Vec2::Zero())
{
}

Vec2 MoveComponent::GetSpeed() const
{
    return mSpeed;
}

void MoveComponent::SetSpeed(Vec2 speed)
{
    mSpeed = speed;
}

void MoveComponent::Update()
{
    if(!Maths::NearZero(mSpeed.MagnitudeSquared()))
    {
        Vec3 newPosition = mOwner->GetTransform().GetPosition() +
            (mOwner->GetTransform().Right() * mSpeed.x +
            mOwner->GetTransform().Up() * mSpeed.y) * Time::deltaTime;
        mOwner->SetLocation(newPosition);
    }
}
