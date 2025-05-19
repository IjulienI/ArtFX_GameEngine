#pragma once
#include "Core/Class/Component/Component.h"
#include "Input/IInputListener.h"

class CharacterMovementComponent;
class DoomPlayer;

class DoomPlayerController : public Component, public IInputListener
{
private:
    DoomPlayer* mPlayer = nullptr;
    CharacterMovementComponent* mMoveComponent = nullptr;
public:
    DoomPlayerController(DoomPlayer* player);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;
    void OnCall(SDL_Event& event) override;
};
