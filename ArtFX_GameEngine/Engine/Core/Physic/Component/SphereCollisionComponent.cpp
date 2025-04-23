#include "SphereCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Component/MeshComponent.h"

SphereCollisionComponent::SphereCollisionComponent(Actor* actor) : BaseCollisionComponent(actor)
{
    mCollisionType = CollisionType::Sphere;
    mRadius = actor->GetComponent<MeshComponent>()->GetMesh()->GetRadius();
}

SphereCollisionComponent::SphereCollisionComponent(Actor* actor, float radius) : BaseCollisionComponent(actor), mRadius(radius)
{
    mCollisionType = CollisionType::Sphere;
}

SphereCollisionComponent::~SphereCollisionComponent() = default;

void SphereCollisionComponent::SetRadius(float radius)
{
    mRadius = radius;
}
