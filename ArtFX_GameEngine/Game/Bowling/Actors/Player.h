#pragma once
#include "Bowling/BowlingState.h"
#include "Core/Class/Actor/Actor.h"

class PinManager;
class RigidbodyComponent;
class BowlingController;

class Player : public Actor
{
private:    
    BowlingController* controller = nullptr;

    PinManager* mPinManager = nullptr;

    Camera* mCamera = nullptr;
    Vec3 mCameraBasePos;
    Quaternion mCameraBaseRot;
    bool mCameraLeft;
    
    Actor* mBowlingball = nullptr;
    Actor* mBowlingBallThrow = nullptr;
    Actor* mBowlingBallForceDirArrow = nullptr;
    Actor* mBowlingBallRotationArrow = nullptr;

    Actor* mPinExtractor = nullptr;

    bool mCanShoot = false;

    float mPower = 0.7f;
    float mRotationPower = 0.0f;

    MeshComponent* mBowlingballMesh = nullptr;

    EBowlingState mBowlingState = EBowlingState::PreShoot;
    int mShootCount = 0;
    float mTimer = 0.0f;
    
public:
    Player();
    ~Player() override = default;

    void Shoot();

    void Move(float movement);
    void Turn(float rotation);

    void ChangePower(float power);
    void ChangeRotation(float rotation);

    void ChangeState(EBowlingState newState);

    void SetPinManger(PinManager* pPinManager)
    {
        mPinManager = pPinManager;
    }

    void SetPinExtractor(Actor* pPinExtractor);

    void Start() override;
    void Update() override;
    void Destroy() override;
    
};
