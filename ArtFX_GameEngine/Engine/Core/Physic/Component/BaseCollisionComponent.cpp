#include "BaseCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/PhysicEngine.h"
#include "Core/Render/Component/MeshComponent.h"

struct Vertex;

BaseCollisionComponent::BaseCollisionComponent(Actor* pOwner) : Component(pOwner), mCollisionType(CollisionType::Box)
{
    PhysicEngine& PhysicInstance = PhysicEngine::GetInstance();
    RigidbodyComponent* rb = mOwner->GetComponent<RigidbodyComponent>();
    rb->SetCollisionComponent(this);
    PhysicInstance.AddRigidbody(rb);
}

BaseCollisionComponent::~BaseCollisionComponent() = default;

std::vector<Vec3> BaseCollisionComponent::GetVerticesInWorldSpace() const
{
    std::vector<Vec3> worldVertices;
    const std::vector<Vertex>& localVertices = mOwner->GetComponent<MeshComponent>()->GetMesh()->GetVertices();

    Vec3 worldPosition = mOwner->GetLocation();
    Quaternion worldRotation = mOwner->GetRotation();

    for (const Vertex& vertex : localVertices) {
        Vec3 worldVertex = worldRotation * vertex.position + worldPosition;
        worldVertices.push_back(worldVertex);
    }

    return worldVertices;
}
