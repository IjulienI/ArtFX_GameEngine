#include "BoxCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Component/MeshComponent.h"

BoxCollisionComponent::BoxCollisionComponent(Actor* owner) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    mBoundingBox = mOwner->GetComponent<MeshComponent>()->GetMesh()->GetBoundingBox();
}

BoxCollisionComponent::BoxCollisionComponent(Actor* owner, const Box box) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    mBoundingBox = box;
}

BoxCollisionComponent::~BoxCollisionComponent() = default;

void BoxCollisionComponent::SetBoundingBox(const Box& box)
{
    mBoundingBox = box;
}
