#include "DoomPlayerController.h"

#include "Doom/Actors/DoomPlayer.h"
#include "Input/InputManager.h"
#include "Math/Time.h"
#include "Miscellaneous/Actor/Camera.h"
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
    InputManager.BindTo(SDL_SCANCODE_SPACE, this);
    
    Component::OnStart();
}

void DoomPlayerController::Update()
{
    Component::Update();

    Actor* Camera = mPlayer->GetCamera();
    
    if (mInputEvents[SDL_SCANCODE_W])
        mMoveComponent->Move(1.0f, Camera->GetTransform().Forward());

    if (mInputEvents[SDL_SCANCODE_S])
        mMoveComponent->Move(-1.0f, Camera->GetTransform().Forward());

    if (mInputEvents[SDL_SCANCODE_A])
        mMoveComponent->Move(-1.0f, Camera->GetTransform().Right());

    if (mInputEvents[SDL_SCANCODE_D])
        mMoveComponent->Move(1.0f, Camera->GetTransform().Right());

    if (mInputEvents[SDL_SCANCODE_SPACE])
    {
        if (!mShoot)
        {
            mShoot = true;
            mPlayer->Shoot();
        }            
    }
    
    if (!mInputEvents[SDL_SCANCODE_SPACE])
    {
        mShoot = false;
    }
    

    SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);
    
    float yawDelta = static_cast<float>(mMouseDeltaX) * mSensitivity * Time::deltaTime;
    
    Camera->Rotate(Vec3(0.0f, 0.0f, yawDelta));
}

void DoomPlayerController::OnEnd()
{ 
    Component::OnEnd();
}

void DoomPlayerController::OnCall(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        bool isPressed = (event.type == SDL_KEYDOWN);
        SDL_Scancode scancode = event.key.keysym.scancode;
        
        mInputEvents[scancode] = isPressed;
    }

}
