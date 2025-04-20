#include "PlayerController.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Input/InputManager.h"

PlayerController::PlayerController(Actor* owner, int updateOrder) : MoveComponent(owner, updateOrder)
{
    PlayerController::OnStart();
}

void PlayerController::OnStart()
{
    InputManager& InputManager = InputManager::Instance();
    InputManager.BindTo(SDL_SCANCODE_W, this);
    InputManager.BindTo(SDL_SCANCODE_S, this);
    InputManager.BindTo(SDL_SCANCODE_A, this);
    InputManager.BindTo(SDL_SCANCODE_D, this);
    
    MoveComponent::OnStart();
}

void PlayerController::OnCall(SDL_Event& event)
{    
    switch (event.key.keysym.scancode)
    {
    case SDL_SCANCODE_W:
        mSpeed.y = event.type == SDL_KEYDOWN ? mWalkSpeed : 0.0f;
        break;
    case SDL_SCANCODE_S:
        mSpeed.y = event.type == SDL_KEYDOWN ? -mWalkSpeed : 0.0f;
        break;
    case SDL_SCANCODE_A:
        mSpeed.x = event.type == SDL_KEYDOWN ? -mWalkSpeed : 0.0f;
        mOwner->GetComponent<SpriteComponent>()->SetFlipX(true);
        break;
    case SDL_SCANCODE_D:
        mSpeed.x = event.type == SDL_KEYDOWN ? mWalkSpeed : 0.0f;
        break;
    default:
        break;
    }
}
