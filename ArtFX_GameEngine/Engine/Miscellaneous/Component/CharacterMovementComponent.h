#pragma once
#include "Core/Class/Component/Component.h"

class CharacterMovementComponent : public Component
{
private:
    int mJumpCount = 0;
    float mWalkSpeed = 0.0f;

    Vec3 mWalkDirection = Vec3::zero;
    
public:
    //--Base
    
    CharacterMovementComponent(Actor* pOwner);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;

    //--Public Values    
    //Movement
    float mMaxWalkSpeed = 10.0f;
    float mWalkAcceleration = 0.2f;
    float mLinearDamping = 0.5f;

    //Jump
    int mMaxJumpCount = 1;
    float mJumpForce = 10.0f;

    //--Public Methods
    void Move(float pIntensity, Vec3 pDirection);
    void Jump();
    
};
