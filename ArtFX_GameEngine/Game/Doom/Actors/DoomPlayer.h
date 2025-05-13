#pragma once
#include "Core/Class/Actor/Actor.h"

class DoomPlayerController;
class CharacterMovementComponent;

class DoomPlayer : public Actor
{
private:
    DoomPlayerController* mPlayerController = nullptr;
    CharacterMovementComponent* mCharacterMovement = nullptr;

    
public:
    DoomPlayer();
    ~DoomPlayer() override = default;

    void Start() override;
    void Update() override;
    void Destroy() override;
    
};
