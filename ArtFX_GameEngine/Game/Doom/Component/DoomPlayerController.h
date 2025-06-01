#pragma once
#include <map>

#include "Core/Class/Component/Component.h"
#include "Input/IInputListener.h"

class CharacterMovementComponent;
class DoomPlayer;

class DoomPlayerController : public Component, public IInputListener
{
private:

    int mMouseDeltaX, mMouseDeltaY;

    float mSensitivity = 2.5f;
    
    DoomPlayer* mPlayer = nullptr;
    
    CharacterMovementComponent* mMoveComponent = nullptr;

    std::map<SDL_Scancode, bool> mInputEvents;      
    
public:
    DoomPlayerController(DoomPlayer* player);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;
    void OnCall(SDL_Event& event) override;
};
