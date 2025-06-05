#include "Pin.h"

#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"

Pin::Pin() : Actor(), mHitted(false)
{
    mClassName = "Pin";
    MeshComponent* meshComponent = new MeshComponent(this);
    meshComponent->SetMesh(Asset::GetMesh("BowlingPin"));
    meshComponent->AddTexture(Asset::GetTexture("BowlingPin"));

    RigidbodyComponent* rigidbodyComponent = new RigidbodyComponent(this);
    rigidbodyComponent->SetMass(0.0f);
    rigidbodyComponent->SetRestitution(0.0f);

    PolyCollisionComponent* collisionComponent = new PolyCollisionComponent(this);

    Rotate(Vec3(45.0f, 0.0f, 0.0f));
    Pin::Start();
}

void Pin::Start()
{

}

void Pin::Update()
{
    Actor::Update();
}

void Pin::Destroy()
{
    Actor::Destroy();
}

void Pin::SetHitted(bool pHitted)
{
    mHitted = pHitted;
}
