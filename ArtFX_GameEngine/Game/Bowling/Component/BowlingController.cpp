#include "BowlingController.h"

#include "Bowling/Actors/Player.h"
#include "Core/Class/Actor/Actor.h"
#include "Input/InputManager.h"
#include "Math/Time.h"


BowlingController::BowlingController(Player* pOwner) : Component(reinterpret_cast<Actor*>(pOwner)), mPlayer(pOwner)
{
    BowlingController::OnStart();
}

void BowlingController::OnStart()
{
    InputManager& InputManager = InputManager::Instance();
    InputManager.BindTo(SDL_SCANCODE_A, this);
    InputManager.BindTo(SDL_SCANCODE_D, this);
    InputManager.BindTo(SDL_SCANCODE_W, this);
    InputManager.BindTo(SDL_SCANCODE_S, this);
    InputManager.BindTo(SDL_SCANCODE_Q, this);
    InputManager.BindTo(SDL_SCANCODE_E, this);
    InputManager.BindTo(SDL_SCANCODE_SPACE, this);
    
    Component::OnStart();
}

void BowlingController::Update()
{
    SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);
    mPlayer->ChangeRotation(static_cast<float>(mMouseDeltaX) * 0.2f * Time::deltaTime);
}

void BowlingController::OnEnd()
{
    Component::OnEnd();
}

void BowlingController::OnCall(SDL_Event& event)
{    
    switch (event.key.keysym.scancode)
    {
    case SDL_SCANCODE_A:
        if (event.type == SDL_KEYDOWN)
            mPlayer->Move(-10.0f);
        break;
    case SDL_SCANCODE_D:
        if (event.type == SDL_KEYDOWN)
            mPlayer->Move(10.0f);
        break;
    case SDL_SCANCODE_Q:
        if (event.type == SDL_KEYDOWN)
            mPlayer->Turn(-100.0f);
        break;
    case SDL_SCANCODE_E:
        if (event.type == SDL_KEYDOWN)
            mPlayer->Turn(100.0f);
        break;
    case SDL_SCANCODE_W:
        if (event.type == SDL_KEYDOWN)
            mPlayer->ChangePower(0.05f);
        break;
    case SDL_SCANCODE_S:
        if (event.type == SDL_KEYDOWN)
            mPlayer->ChangePower(-0.05f);
        break;
    case SDL_SCANCODE_SPACE:
        if (event.type == SDL_KEYDOWN)
            mPlayer->Shoot();
        break;
    }
}
