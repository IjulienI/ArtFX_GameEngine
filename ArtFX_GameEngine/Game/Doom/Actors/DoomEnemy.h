#pragma once
#include "Core/Class/Actor/Actor.h"

class RigidbodyComponent;
class BoxCollisionComponent;

class DoomEnemy : public Actor
{
private:
    MeshComponent* mMeshComponent = nullptr;

    Actor* mPlayer = nullptr;

    RigidbodyComponent* mRigidbodyComponent = nullptr;
    BoxCollisionComponent* mBoxCollisionComponent = nullptr;

    int mHealth = 100;

    //Shoot
    Vec2 mShootRandomDelay = Vec2(2, 4);
    float mShootDelay = mShootRandomDelay.y; 
    float mShootTimer = 0.0f;

    float mCurrentFrame = 0.0f;
    float mAnimationFps = 12.0f;

    void Shoot();
    void LookAt();

    bool mDead = false;

public:
    DoomEnemy(Actor* pPlayer);
    ~DoomEnemy() override;
    void Start() override;
    void Update() override;
    void Destroy() override;
    void ApplyDamage(float damage);
};
