#include "Scenes/Base/BaseScene.h"

#include "Actor/Skybox.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"

BaseScene::BaseScene()
{
}

void BaseScene::Start()
{
    Scene::Start();
    //SkyBox
    Skybox* skybox = new Skybox();
    AddActor(skybox);

    //Floor
    Actor* floor = new Actor();
    AddActor(floor);

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));
    floor->Rotate(Vec3(90.0f, 0.0f, 0.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));
}

void BaseScene::Update()
{
    Scene::Update();
    
}

void BaseScene::Render()
{
    Scene::Render();
}

void BaseScene::Close() const
{
    Scene::Close();
}

void BaseScene::Load()
{
    Scene::Load();
    //Load Textures
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Floor.png", "Floor");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Floor.obj", "Floor");
}
