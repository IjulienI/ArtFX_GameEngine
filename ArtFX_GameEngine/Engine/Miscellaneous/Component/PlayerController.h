#pragma once
#include "MoveComponent.h"
#include "Input/IInputListener.h"

class PlayerController : public MoveComponent, public IInputListener
{
protected:
    float mWalkSpeed = 100.0f;
    
public:
    PlayerController(Actor* owner, int updateOrder = 100);
    PlayerController() = delete;
    PlayerController(const PlayerController&) = delete;
    PlayerController& operator= (const PlayerController&) = delete;

    void OnStart() override;

    void OnCall(SDL_Event& event) override;
};
