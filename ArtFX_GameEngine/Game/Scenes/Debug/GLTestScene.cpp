#include "GLTestScene.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Core/Render/OpenGL/RendererGL.h"

GLTestScene::GLTestScene()
{
}

void GLTestScene::Start()
{
    Scene::Start();
    Square = new Actor();
    AddActor(Square);

    Square->SetLocation({800.0f, 800.0f});
    Square->SetScale({1, 1});

    SpriteComponent* sprite = new SpriteComponent(Square, Asset::GetTexture("TUTUTUTU"));
}

void GLTestScene::Update()
{
    Scene::Update();
}

void GLTestScene::Render()
{
    Scene::Render();
}

void GLTestScene::Close() const
{
    Scene::Close();
}

void GLTestScene::Load()
{
    Scene::Load();
    Asset::LoadTexture(*mRenderer, "Resources/TUTUTUTU.png", "TUTUTUTU");
    
    mFragmentShader->Load("SpriteShader.frag", FRAGMENT);
    mVertexShader->Load("SpriteShader.vert", VERTEX);

    mSimpleProgram.Compose({mFragmentShader, mVertexShader});

    mRenderer->SetShaderProgram(&mSimpleProgram);    
}
