

#include "DoomScene.h"

#include "Actor/Skybox.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/BoxCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Doom/Actors/DoomPlayer.h"
#include "Math/Time.h"

DoomScene::DoomScene()
{
}

void DoomScene::Start()
{
    Scene::Start();
    //SkyBox
    Skybox* skybox = new Skybox();
    AddActor(skybox);

    //Floor
    Actor* floor = new Actor();
    AddActor(floor);

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* floorRigidbody = new RigidbodyComponent(floor);
    floorRigidbody->SetMass(0.0f);

    BoxCollisionComponent* floorPolyCollision = new BoxCollisionComponent(floor);

    DoomPlayer* player = new DoomPlayer();
    AddActor(player);
    
}

void DoomScene::Update()
{
    Scene::Update();
    
}

void DoomScene::Render()
{
    Scene::Render();
}

void DoomScene::Close() const
{
    Scene::Close();
}

void DoomScene::Load()
{
    Scene::Load();
    //Load Textures
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Floor.png", "Floor");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Floor.obj", "Floor");
}
