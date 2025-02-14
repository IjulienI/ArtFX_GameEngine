#include "DebugCollisionScene.h"

#include "Actor/NDebugCollisions.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Class/Actor/ActorState.h"
#include "Math/Transform2D.h"

DebugCollisionScene::DebugCollisionScene() : Scene()
{
}

void DebugCollisionScene::Start()
{
    NDebugCollisions* blaz = new NDebugCollisions(Transform2D(),*this, ActorState::Active);
    AddActor(blaz);
    Scene::Start();
}

void DebugCollisionScene::OnInput(SDL_Event sdl_event)
{
    
}

void DebugCollisionScene::Render() const
{
    Scene::Render();
    mRenderer->BeginDraw();
    Rectangle hello = Rectangle(350,350,150,150);
    mRenderer->DrawRect(hello, 255,0,0, 255);
    mRenderer->EndDraw();
}

