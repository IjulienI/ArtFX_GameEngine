#include "DoomPlayer.h"

#include "DoomEnemy.h"
#include "Core/Physic/TraceSystem.h"
#include "Core/Physic/Component/BoxCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Debug/Log.h"
#include "Doom/Component/DoomPlayerController.h"
#include "Miscellaneous/Actor/Camera.h"
#include "Miscellaneous/Component/CharacterMovementComponent.h"

DoomPlayer::DoomPlayer() : Actor()
{
    //Set default values
    mClassName = "DoomPlayer";
    mName = "DoomPlayer_01";

    Asset::LoadTexture(mScene->GetRenderer(), "Resources/Textures/EmptyTexture.png", "EmptyTexture");

    //Set Initial variables    
    mCharacterMovement = new CharacterMovementComponent(this);
    mPlayerController = new DoomPlayerController(this);
    mCamera = dynamic_cast<Camera*>(mScene->GetActors()[0]);

    MeshComponent* meshComponent = new MeshComponent(this);
    meshComponent->SetMesh(Asset::GetMesh("DoomGuy"));
    meshComponent->AddTexture(Asset::GetTexture("EmptyTexture"));

    mRigidbodyComponent = new RigidbodyComponent(this);
    mRigidbodyComponent->SetMass(0.1f);
    mRigidbodyComponent->SetLockRotation(true);
    mRigidbodyComponent->SetGravityScale(0.0f);
    mRigidbodyComponent->SetVelocityMultiplier(Vec3(1.0f, 1.0f, 0.0f));

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

void DoomPlayer::Shoot()
{
    Vec3 position = mTransform.GetPosition();
    Vec3 direction = mCamera->GetTransform().Forward() * 1000.0f;
    
    HitResult hitResult = TraceSystem::LineTrace(position, direction, mRigidbodyComponent, true);

    if (hitResult.hit && hitResult.hitActor->GetClass() == "DoomEnemy")
    {
        dynamic_cast<DoomEnemy*>(hitResult.hitActor)->ApplyDamage(25);
    }
}

void DoomPlayer::ApplyDamage(int damage)
{
    mHealth -= damage;
    if (mHealth <= 0)
    {
        Log::Info("DoomPlayer is dead.");
    }
}
