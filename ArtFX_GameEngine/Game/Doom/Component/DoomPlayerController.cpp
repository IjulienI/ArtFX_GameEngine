#include "DoomPlayerController.h"

#include "Doom/Actors/DoomPlayer.h"
#include "Input/InputManager.h"
#include "Miscellaneous/Component/CharacterMovementComponent.h"

DoomPlayerController::DoomPlayerController(DoomPlayer* player) : Component(reinterpret_cast<Actor*>(player))
{
    mPlayer = player;
    mMoveComponent = player->GetCharacterMovement();
    DoomPlayerController::OnStart();
}

void DoomPlayerController::OnStart()
{
    InputManager& InputManager = InputManager::Instance();
    InputManager.BindTo(SDL_SCANCODE_W, this);
    InputManager.BindTo(SDL_SCANCODE_S, this);
    InputManager.BindTo(SDL_SCANCODE_A, this);
    InputManager.BindTo(SDL_SCANCODE_D, this);
    
    Component::OnStart();
}

void DoomPlayerController::Update()
{
    Component::Update();
}

void DoomPlayerController::OnEnd()
{
    Component::OnEnd();
}

void DoomPlayerController::OnCall(SDL_Event& event)
{
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
                mMoveComponent->Move(1.0f, mPlayer->GetTransform().Forward());
            break;
        case SDL_SCANCODE_S:
                mMoveComponent->Move(-1.0f, mPlayer->GetTransform().Forward());
            break;
        case SDL_SCANCODE_A:
                mMoveComponent->Move(1.0f, mPlayer->GetTransform().Up());
            break;
        case SDL_SCANCODE_D:
                mMoveComponent->Move(-1.0f, mPlayer->GetTransform().Up());
            break;
        default:
            break;
        }

}
