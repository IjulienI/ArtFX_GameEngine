#pragma once
#include "Core/Class/Component/Component.h"
#include "Input/IInputListener.h"

class Player;

class BowlingController : public Component, IInputListener
{
private:
    Player* mPlayer;
    int mMouseDeltaX, mMouseDeltaY;
    
public:
    BowlingController(Player* pOwner);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;
    void OnCall(SDL_Event& event) override;
    
};
