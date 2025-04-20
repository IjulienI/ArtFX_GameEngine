#include "GLTestScene.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"

GLTestScene::GLTestScene()
{
}

void GLTestScene::Start()
{
    Scene::Start();
    
    Actor* Square = new Actor();
    AddActor(Square);

    Square->SetLocation(Vec3(0.0f, 0.0f, -10.0f));
    Square->SetScale(Vec3(1.0f, 1.0f, 1.0f));
    Square->Rotate(Vec3(90.0f, 0.0f, 0.0f));

    MeshComponent* meshComponent = new MeshComponent(Square);
    meshComponent->SetMesh(Asset::GetMesh("Quille"));
    meshComponent->AddTexture(Asset::GetTexture("Quille"));

    //SkyBox
    Actor* Skybox = new Actor();
    AddActor(Skybox);
    
    Skybox->SetScale(Vec3(1000.0f, 1000.0f, 1000.0f));
    Skybox->Rotate(Vec3(90.0f, 0.0f, 0.0f));

    MeshComponent* skyboxMeshComponent = new MeshComponent(Skybox); 
    skyboxMeshComponent->SetMesh(Asset::GetMesh("Skybox"));
    skyboxMeshComponent->AddTexture(Asset::GetTexture("Skybox"));
}

void GLTestScene::Update()
{
    Scene::Update();
    //mActors[1]->Rotate(Vec3(Maths::ToRad(10) * Time::deltaTime, Maths::ToRad(10) * Time::deltaTime, Maths::ToRad(10) * Time::deltaTime));
   //mActors[2]->Rotate(Vec3(Maths::ToRad(10) * Time::deltaTime, 0.0f, 0.0f));
    Log::Info( "Rotation : " + std::to_string(mActors[2]->GetTransform().GetRotation().x));
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
    Asset::LoadTexture(*mRenderer, "Resources/Textures/QuilleTex.png", "Quille");
    Asset::LoadMesh("Quille.obj", "Quille");    
    Asset::LoadMesh("Box.obj", "Skybox");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Skybox.png", "Skybox");
}
