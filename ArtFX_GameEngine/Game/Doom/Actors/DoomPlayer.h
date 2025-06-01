#pragma once
#include "Core/Class/Actor/Actor.h"

class DoomPlayerController;
class CharacterMovementComponent;

class DoomPlayer : public Actor
{
private:
    DoomPlayerController* mPlayerController = nullptr;
    CharacterMovementComponent* mCharacterMovement = nullptr;
    Camera* mCamera = nullptr;

    
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
    
};
