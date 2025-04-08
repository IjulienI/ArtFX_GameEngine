#include "Component.h"

#include "Core/Class/Actor/Actor.h"

Component::Component(Actor* owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::SetTransform(Matrix4Row pWorldTransform)
{
    mWorldTransform = pWorldTransform;
}

void Component::OnStart()
{
    
}

void Component::Update()
{
    
}

void Component::OnEnd()
{
    
}
