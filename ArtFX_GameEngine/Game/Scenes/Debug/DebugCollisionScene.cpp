#include "DebugCollisionScene.h"

#include <format>

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/AnimatedSpriteComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Miscellaneous/Component/MoveComponent.h"
#include "Miscellaneous/Component/PlayerController.h"


DebugCollisionScene::DebugCollisionScene() : Scene(nullptr, "DebugScene")
{
}

void DebugCollisionScene::Start()
{
    Asset::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/00_bSpell.png", "00_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/01_bSpell.png", "01_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/02_bSpell.png", "02_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/03_bSpell.png", "03_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/04_bSpell.png", "04_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/05_bSpell.png", "05_bSpell");
    Asset::LoadTexture(*mRenderer, "Resources/Animations/Spell/06_bSpell.png", "06_bSpell");

    std::vector<Texture*> spellAnim;
    for(int i = 0 ; i < 5 ; i++)
    {
        spellAnim.push_back(&Asset::GetTexture(std::format("0{}_bSpell", i)));
    }
    
    Actor* pokeball = new Actor();
    AddActor(pokeball);
    
    SpriteComponent* sprite =  new SpriteComponent(pokeball, Asset::GetTexture("ball"));
    pokeball->SetLocation({800.0f, 800.0f});
    pokeball->SetScale({0.5f, 0.5f});
    
    Actor* player = new Actor();
    AddActor(player);
    
    AnimatedSpriteComponent* playerSprite = new AnimatedSpriteComponent(player, spellAnim);
    player->SetLocation({50.0f,50.0f});
    playerSprite->SetAnimationFps(8.0f);
    
    PlayerController* playerMovement = new PlayerController(player);
    
    Scene::Start();
}
