#include "DoomPlayer.h"

#include "Doom/Component/DoomPlayerController.h"
#include "Miscellaneous/Actor/Camera.h"
#include "Miscellaneous/Component/CharacterMovementComponent.h"

DoomPlayer::DoomPlayer() : Actor()
{
    //Set default values
    mClassName = "DoomPlayer";
    mName = "DoomPlayer_01";

    //Set Initial variables    
    mCharacterMovement = new CharacterMovementComponent(this);
    mPlayerController = new DoomPlayerController(this);
    mCamera = dynamic_cast<Camera*>(mScene->GetActors()[0]);
}

void DoomPlayer::Start()
{
    Actor::Start();
    

}

void DoomPlayer::Update()
{
    Actor::Update();
    mCamera->SetRotation(mTransform.GetRotation());
    mCamera->Rotate(Vec3(-90.0f, 0.0f, 0.0f));
    mCamera->SetLocation(mTransform.GetPosition() + Vec3(0.0f, 0.0f, 2.0f));
}

void DoomPlayer::Destroy()
{
    Actor::Destroy();
}
