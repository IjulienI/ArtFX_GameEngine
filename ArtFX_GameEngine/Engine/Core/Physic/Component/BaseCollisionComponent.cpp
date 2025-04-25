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
    Scene::ActiveScene->GetRenderer().AddCollision(this);
}

BaseCollisionComponent::~BaseCollisionComponent()
{
    Scene::ActiveScene->GetRenderer().RemoveCollision(this);
};

void BaseCollisionComponent::Draw(Matrix4Row viewProj)
{
    struct Box
    {
        Vec3 min;
        Vec3 max;
    };
}
