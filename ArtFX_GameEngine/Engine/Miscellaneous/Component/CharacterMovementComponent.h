#pragma once
#include "Core/Class/Component/Component.h"

class CharacterMovementComponent : public Component
{
private:
    int mJumpCount = 0;
    Vec3 mWalkSpeed = Vec3::zero;

    bool mMoving = false;
    
public:
    //--Base
    
    CharacterMovementComponent(Actor* pOwner);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;

    //--Public Values    
    //Movement
    float mMaxWalkSpeed = 1000.0f;
    float mWalkAcceleration = 0.2f;
    float mLinearDamping = 2.0f;

    //Jump
    int mMaxJumpCount = 1;
    float mJumpForce = 10.0f;

    //--Public Methods
    void Move(float pIntensity, Vec3 pDirection);
    void Jump();
    
};
