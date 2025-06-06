#include "DoomEnemy.h"

#include "DoomPlayer.h"
#include "Core/Physic/Component/BoxCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Math/Time.h"
#include <algorithm>
#include <random>

#include "Debug/Log.h"

static std::default_random_engine rng(std::random_device{}());

DoomEnemy::DoomEnemy(Actor* pPlayer) : Actor(), mPlayer(pPlayer)
{
    Asset::LoadMesh("Doom/DoomEnemies.obj", "doomEnemy");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_Stand0.png", "Marine_Stand");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_Shoot0.png", "Marine_Shoot");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death1.png", "Marine_death1");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death2.png", "Marine_death2");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death3.png", "Marine_death3");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death4.png", "Marine_death4");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death5.png", "Marine_death5");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death6.png", "Marine_death6");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death7.png", "Marine_death7");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death8.png", "Marine_death8");
    Asset::LoadTexture( mScene->GetRenderer(),"Resources/Textures/Doom/Marine_death0.png", "Marine_death0");
    mClassName = "DoomEnemy";
}

DoomEnemy::~DoomEnemy()
{
}

void DoomEnemy::Shoot()
{
    dynamic_cast<DoomPlayer*>(mPlayer)->ApplyDamage(1);
    mMeshComponent->SetTextureIndex(0);
    mCurrentFrame = 0.0f;
}

void DoomEnemy::LookAt()
{
    Vec3 enemyPos = mTransform.GetPosition();
    Vec3 playerPos = mPlayer->GetLocation();
    Vec2 direction = Vec2(playerPos.x - enemyPos.x, playerPos.y - enemyPos.y);
    float angle = atan2(direction.y, direction.x);
    
    Quaternion rot(Vec3::unitZ, angle);
    SetRotation(rot);
}

void DoomEnemy::Start()
{
    Actor::Start();
    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Asset::GetMesh("doomEnemy"));    
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_Shoot"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_Stand"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death0"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death1"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death2"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death3"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death4"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death5"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death6"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death7"));
    mMeshComponent->AddTexture(Asset::GetTexture("Marine_death8"));

    mMeshComponent->SetTextureIndex(1);

    mRigidbodyComponent = new RigidbodyComponent(this);
    mRigidbodyComponent->SetMass(0.0f);

    mBoxCollisionComponent = new BoxCollisionComponent(this);
    mBoxCollisionComponent->SetBoundingBox({Vec3(-4.0f, 0.0f, -4.0f), Vec3(4.0f, 8.0f, 4.0f)});
}

void DoomEnemy::Update()
{
    Actor::Update();
    LookAt();
    
    if (mDead)
    {
        mCurrentFrame += mAnimationFps * Time::deltaTime;
        mCurrentFrame = std::min(mCurrentFrame, 9.0f);
        mMeshComponent->SetTextureIndex(static_cast<int>(mCurrentFrame));
        return;
    }

    mCurrentFrame += mAnimationFps * Time::deltaTime;
    mCurrentFrame = std::min(mCurrentFrame, 1.0f);
    mMeshComponent->SetTextureIndex(static_cast<int>(mCurrentFrame));
    
    Vec3 Loc = GetLocation();
    if (mPlayer->GetLocation().Distance(Loc) < 50.0f)
    {
        mShootTimer += Time::deltaTime;
        if (mShootTimer >= mShootDelay)
        {
            Shoot();
            mShootTimer = 0.0f;
            std::uniform_real_distribution<float> dist(mShootRandomDelay.x, mShootRandomDelay.y);
            mShootDelay = dist(rng);
        }
    }
}

void DoomEnemy::Destroy()
{
    Actor::Destroy();
}

void DoomEnemy::ApplyDamage(float damage)
{
    if (mDead) return;
    
    mHealth -= static_cast<int>(damage);
    if (mHealth <= 0)
    {
         mDead = true;
        mCurrentFrame = 2.0f;
    }
}
