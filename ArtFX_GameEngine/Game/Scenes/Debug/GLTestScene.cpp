#include "GLTestScene.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Math/Time.h"

GLTestScene::GLTestScene()
{
}

void GLTestScene::Start()
{
    Scene::Start();
    
    Actor* Square = new Actor();
    AddActor(Square);

    Square->SetLocation(Vec3(50.0f, 0.0f, 0.0f));
    Square->SetScale(Vec3(10.0f, 10.0f, 10.0f));

    MeshComponent* meshComponent = new MeshComponent(Square);
}

void GLTestScene::Update()
{
    Scene::Update();
    mActors[1]->Rotate(Vec3(Maths::ToRad(10) * Time::deltaTime, Maths::ToRad(10) * Time::deltaTime, Maths::ToRad(10) * Time::deltaTime));
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
}
