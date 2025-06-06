/**
 * @file BaseCollisionComponent.cpp
 * @brief Implementation of the BaseCollisionComponent class, the base class for all collision components.
 */

#include "BaseCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/PhysicEngine.h"
#include "Core/Render/Component/MeshComponent.h"

struct Vertex;

/**
 * @brief Constructs a BaseCollisionComponent and registers it with the physics and rendering systems.
 * @param pOwner Pointer to the owning Actor.
 */
BaseCollisionComponent::BaseCollisionComponent(Actor* pOwner) : Component(pOwner), mCollisionType(CollisionType::Box)
{
    PhysicEngine& PhysicInstance = PhysicEngine::GetInstance();
    RigidbodyComponent* rb = mOwner->GetComponent<RigidbodyComponent>();
    rb->SetCollisionComponent(this);
    PhysicInstance.AddRigidbody(rb);
    Scene::ActiveScene->GetRenderer().AddCollision(this);
}

/**
 * @brief Destructor for BaseCollisionComponent. Unregisters from the renderer.
 */
BaseCollisionComponent::~BaseCollisionComponent()
{
    Scene::ActiveScene->GetRenderer().RemoveCollision(this);
};

/**
 * @brief Draws the collision shape. To be overridden by derived classes.
 * @param viewProj The view-projection matrix.
 */
void BaseCollisionComponent::Draw(Matrix4Row viewProj)
{
    struct Box
    {
        Vec3 min;
        Vec3 max;
    };
}
