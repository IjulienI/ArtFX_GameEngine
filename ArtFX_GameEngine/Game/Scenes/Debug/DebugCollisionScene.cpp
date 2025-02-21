#include "DebugCollisionScene.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/SpriteComponent.h"


DebugCollisionScene::DebugCollisionScene() : Scene(nullptr, "DebugScene")
{
}

void DebugCollisionScene::Start()
{
    Asset::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    Actor* actor = new Actor();
    AddActor(actor);
    SpriteComponent* sprite =  new SpriteComponent(actor, Asset::GetTexture("ball"));
    actor->SetLocation(Vec2{400, 400});
    Scene::Start();
}

void DebugCollisionScene::OnInput(SDL_Event sdl_event)
{
    
}


