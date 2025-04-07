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
    Actor* Square = new Actor();
    AddActor(Square);

    //SpriteComponent* sprite =  new SpriteComponent(Square, Asset::GetTexture("ball") );
    Square->SetLocation({800.0f, 800.0f});
    Square->SetScale({0.5f, 0.5f});
}

void GLTestScene::Update()
{
    Scene::Update();
}

void GLTestScene::Close() const
{
    Scene::Close();
}

void GLTestScene::Load()
{
    Scene::Load();
    Asset::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    
    mFragmentShader->Load("Simple.frag", FRAGMENT);
    mVertexShader->Load("Simple.vert", VERTEX);

    mSimpleProgram.Compose({mFragmentShader, mVertexShader});

    mRenderer->SetShaderProgram(&mSimpleProgram);    
}
