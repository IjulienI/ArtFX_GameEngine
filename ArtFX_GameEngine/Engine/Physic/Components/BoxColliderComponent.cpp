#include "BoxColliderComponent.h"

#include "../../../Engine/Core/Class/Actor/Actor.h"

BoxColliderComponent::BoxColliderComponent(Actor& owner, Vec2 size, int updateOrder, float maxDistance) : Component(owner, updateOrder), mSize(size), mMaxDistance(maxDistance)
{
    
}

void BoxColliderComponent::OnStart()
{
    Component::OnStart();
    mScene = mOwner.GetScene();
}

void BoxColliderComponent::Update()
{
    Component::Update();
    mCollision = false;
    for(Actor* actor : mScene->GetActors())
    {
        if(mOwner.GetLocation().Distance(actor->GetLocation()) > mMaxDistance) return;
        
        BoxColliderComponent* boxCollider = actor->GetComponent<BoxColliderComponent>();
        if(!boxCollider) return;
        
        if(Collision(boxCollider, actor->GetLocation()))
        {
            mCollision = true;
        }
    }
}

void BoxColliderComponent::OnEnd()
{
    Component::OnEnd();
}

bool BoxColliderComponent::Collision(BoxColliderComponent* component,Vec2 actorLocation)
{
    int xMinA = (int)(mOwner.GetLocation().x);
    int yMinA = (int)(mOwner.GetLocation().y);
    int xMaxA = (int)(mOwner.GetLocation().x + mSize.x);
    int yMaxA = (int)(mOwner.GetLocation().y + mSize.y);
    int xMinB = (int)(actorLocation.x);
    int yMinB = (int)(actorLocation.y);
    int xMaxB = (int)(actorLocation.x + component->GetSize().x);
    int yMaxB = (int)(actorLocation.y + component->GetSize().y);
	
    return (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

Vec2 BoxColliderComponent::GetSize()
{
    return mSize;
}
