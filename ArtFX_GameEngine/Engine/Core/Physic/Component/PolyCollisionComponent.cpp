#include "PolyCollisionComponent.h"

#include "Core/Render/Component/MeshComponent.h"

PolyCollisionComponent::PolyCollisionComponent(Actor* owner) : BoxCollisionComponent(owner)
{
    mCollisionType = CollisionType::Mesh;
    mMesh = mOwner->GetComponent<MeshComponent>()->GetMesh();
}

PolyCollisionComponent::~PolyCollisionComponent() = default;

Mesh* PolyCollisionComponent::GetMesh()
{
    return mMesh;
}
