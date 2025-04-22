#include "RigidbodyComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Math/Time.h"

RigidbodyComponent::RigidbodyComponent(Actor* pOwner) : Component(pOwner), 
    mIsStatic(false), mIsColliding(false)
{
}

void RigidbodyComponent::OnStart()
{
    Component::OnStart();
}

void RigidbodyComponent::Update()
{
    Component::Update();
    std::deque<Actor*> actors = mOwner->GetScene()->GetActors();    
    std::vector<RigidbodyComponent*> rbComponents;
    for (Actor* actor : actors)
    {
        if (actor == mOwner) continue;
        if (RigidbodyComponent* rb = actor->GetComponent<RigidbodyComponent>())
        {
            rbComponents.push_back(rb);
        }
    }
    
    if (mIsStatic || mIsColliding)
        return;
    
    Vec3 previousLocation = mOwner->GetTransform().GetPosition();
    previousLocation.z -= Maths::GRAVITY * Time::deltaTime;
    mOwner->SetLocation(previousLocation);
}

void RigidbodyComponent::OnEnd()
{
    Component::OnEnd();
}

void RigidbodyComponent::SetStatic(bool pStatic)
{
    mIsStatic = pStatic;
}

void RigidbodyComponent::SetColliding(bool pColliding)
{
    mIsColliding = pColliding;
}
