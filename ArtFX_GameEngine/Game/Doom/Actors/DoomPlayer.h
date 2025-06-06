#pragma once
#include "Core/Class/Actor/Actor.h"

class RigidbodyComponent;
class DoomPlayerController;
class CharacterMovementComponent;

class DoomPlayer : public Actor
{
private:
    DoomPlayerController* mPlayerController = nullptr;
    CharacterMovementComponent* mCharacterMovement = nullptr;
    Camera* mCamera = nullptr;
    RigidbodyComponent* mRigidbodyComponent = nullptr;

    int mHealth = 5;    
public:
    DoomPlayer();
    ~DoomPlayer() override = default;

    CharacterMovementComponent* GetCharacterMovement() const
    {
        return mCharacterMovement;
    }

    Camera* GetCamera() const
    {
        return mCamera;
    }

    void Start() override;
    void Update() override;
    void Destroy() override;
    void Shoot();

    void ApplyDamage(int damage);
    
};
