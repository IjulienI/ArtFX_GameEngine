#include "DoomPlayer.h"

#include "Core/Physic/Component/BoxCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Doom/Component/DoomPlayerController.h"
#include "Miscellaneous/Actor/Camera.h"
#include "Miscellaneous/Component/CharacterMovementComponent.h"

DoomPlayer::DoomPlayer() : Actor()
{
    //Set default values
    mClassName = "DoomPlayer";
    mName = "DoomPlayer_01";

    //Set Initial variables    
    mCharacterMovement = new CharacterMovementComponent(this);
    mPlayerController = new DoomPlayerController(this);
    mCamera = dynamic_cast<Camera*>(mScene->GetActors()[0]);

    MeshComponent* meshComponent = new MeshComponent(this);
    meshComponent->SetMesh(Asset::GetMesh("DoomGuy"));

    RigidbodyComponent* rigidbodyComponent = new RigidbodyComponent(this);
    rigidbodyComponent->SetMass(0.1f);
    rigidbodyComponent->SetLockRotation(true);
    rigidbodyComponent->SetGravityScale(0.0f);

    BoxCollisionComponent* boxCollisionComponent = new BoxCollisionComponent(this);
}

void DoomPlayer::Start()
{
    Actor::Start();
}

void DoomPlayer::Update()
{
    Actor::Update();
    mCamera->SetLocation(mTransform.GetPosition() + Vec3(0.0f, 0.0f, 2.0f));
    mTransform.ForceComputeWorldTransform();
}

void DoomPlayer::Destroy()
{
    Actor::Destroy();
}
