#include "DoomPlayer.h"

#include "Doom/Component/DoomPlayerController.h"
#include "Miscellaneous/Component/CharacterMovementComponent.h"

DoomPlayer::DoomPlayer() : Actor()
{
    //Set default values
    mClassName = "DoomPlayer";
    mName = "DoomPlayer_01";

    //Set Initial variables
    mPlayerController = new DoomPlayerController(this);
    mCharacterMovement = new CharacterMovementComponent(this);
}

void DoomPlayer::Start()
{
    Actor::Start();
}

void DoomPlayer::Update()
{
    Actor::Update();
}

void DoomPlayer::Destroy()
{
    Actor::Destroy();
}
