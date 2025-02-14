#include "BoxColliderComponent.h"

#include "../../../Engine/Core/Class/Actor/Actor.h"
#include "Debug/Log.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, Vec2 size, int updateOrder, float maxDistance) : Component(owner, updateOrder), mSize(size), mMaxDistance(maxDistance)
{
    
}

void BoxColliderComponent::OnStart()
{
    Component::OnStart();
    mScene = mOwner->GetScene();
}

void BoxColliderComponent::Update()
{
    Component::Update();
    for(Actor* actor : mScene->GetActors())
    {
        if(actor == mOwner) return;
        
        if(mOwner->GetLocation().Distance(actor->GetLocation()) > mMaxDistance) return;
        
        BoxColliderComponent* boxCollider = actor->GetComponent<BoxColliderComponent>();
        if(!boxCollider) return;
        
        if(Collision(boxCollider, actor->GetLocation()))
        {
            OnCollision(actor);
        }
    }
}

void BoxColliderComponent::OnEnd()
{
    Component::OnEnd();
}

bool BoxColliderComponent::Collision(BoxColliderComponent* component,Vec2 actorLocation) const
{
    int xMinA = static_cast<int>(mOwner->GetLocation().x);
    int yMinA = static_cast<int>(mOwner->GetLocation().y);
    int xMaxA = static_cast<int>(mOwner->GetLocation().x + mSize.x);
    int yMaxA = static_cast<int>(mOwner->GetLocation().y + mSize.y);
    int xMinB = static_cast<int>(actorLocation.x);
    int yMinB = static_cast<int>(actorLocation.y);
    int xMaxB = static_cast<int>(actorLocation.x + component->GetSize().x);
    int yMaxB = static_cast<int>(actorLocation.y + component->GetSize().y);
	
    return (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

void BoxColliderComponent::OnCollision(Actor* actor)
{
    Log::Info("Overlap detected");
}

Vec2 BoxColliderComponent::GetSize()
{
    return mSize;
}
