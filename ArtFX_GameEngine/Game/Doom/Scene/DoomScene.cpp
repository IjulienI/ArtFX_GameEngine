

#include "DoomScene.h"

#include "Actor/Skybox.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/BoxCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Doom/Actors/DoomEnemy.h"
#include "Doom/Actors/DoomPlayer.h"
#include "Doom/Actors/DoomWidget.h"
#include "Math/Time.h"

DoomScene::DoomScene()
{
}

void DoomScene::Start()
{
    Scene::Start();

    DoomPlayer* player = new DoomPlayer();
    AddActor(player);

    player->SetLocation(Vec3(0.0f, 0.0f, -6.0f));

    DoomEnemy* enemy0 = new DoomEnemy(player);
    AddActor(enemy0);

    enemy0->SetLocation(Vec3(0.0f, 55.0f, -6.0f));

    DoomEnemy* enemy1 = new DoomEnemy(player);
    AddActor(enemy1);

    enemy1->SetLocation(Vec3(25.0f, 55.0f, -6.0f));

    DoomEnemy* enemy2 = new DoomEnemy(player);
    AddActor(enemy2);

    enemy2->SetLocation(Vec3(55.0f, -55.0f, -6.0f));

    DoomEnemy* enemy3 = new DoomEnemy(player);
    AddActor(enemy3);

    enemy3->SetLocation(Vec3(-77.0f, -75.0f, -6.0f));

    SpawnWalls();

    DoomWidget* widget = new DoomWidget();
    AddActor(widget);
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
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Doom/DoomFloor.png", "Floor");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Doom/DoomWall.png", "Wall");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Doom/DoomRoof.png", "Roof");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Doom/DoomFloor.obj", "Floor");
    Asset::LoadMesh("Doom/DoomRoof.obj", "Roof");
    Asset::LoadMesh("Doom/DoomWall.obj", "Wall");
    Asset::LoadMesh("Doom/Collision/DoomPlayerHitBox.obj", "DoomGuy");
}

void DoomScene::SpawnWalls()
{
    //WALLS
    Actor* wall = new Actor();
    AddActor(wall);

    wall->SetLocation(Vec3(100.0f, 0.0f, -10.0f));

    MeshComponent* wallMeshComponent = new MeshComponent(wall);
    wallMeshComponent->SetMesh(Asset::GetMesh("Wall"));
    wallMeshComponent->AddTexture(Asset::GetTexture("Wall"));

    RigidbodyComponent* wallRigidbody = new RigidbodyComponent(wall);
    wallRigidbody->SetMass(0.0f);

    BoxCollisionComponent* wallPolyCollision = new BoxCollisionComponent(wall);

    Actor* wall2 = new Actor();
    AddActor(wall2);

    wall2->SetLocation(Vec3(-100.0f, 0.0f, -10.0f));
    wall2->Rotate(Vec3(0.0f, 0.0f, 180.0f));

    MeshComponent* wall2MeshComponent = new MeshComponent(wall2);
    wall2MeshComponent->SetMesh(Asset::GetMesh("Wall"));
    wall2MeshComponent->AddTexture(Asset::GetTexture("Wall"));

    RigidbodyComponent* wall2Rigidbody = new RigidbodyComponent(wall2);
    wall2Rigidbody->SetMass(0.0f);

    BoxCollisionComponent* wall2PolyCollision = new BoxCollisionComponent(wall2);

    Actor* wall3 = new Actor();
    AddActor(wall3);

    wall3->SetLocation(Vec3(0.0f, 100.0f, -10.0f));
    wall3->Rotate(Vec3(0.0f, 0.0f, 90.0f));

    MeshComponent* wall3MeshComponent = new MeshComponent(wall3);
    wall3MeshComponent->SetMesh(Asset::GetMesh("Wall"));
    wall3MeshComponent->AddTexture(Asset::GetTexture("Wall"));

    RigidbodyComponent* wall3Rigidbody = new RigidbodyComponent(wall3);
    wall3Rigidbody->SetMass(0.0f);

    BoxCollisionComponent* wall3PolyCollision = new BoxCollisionComponent(wall3);

    Actor* wall4 = new Actor();
    AddActor(wall4);

    wall4->SetLocation(Vec3(0.0f, -100.0f, -10.0f));
    wall4->Rotate(Vec3(0.0f, 0.0f, -90.0f));

    MeshComponent* wall4MeshComponent = new MeshComponent(wall4);
    wall4MeshComponent->SetMesh(Asset::GetMesh("Wall"));
    wall4MeshComponent->AddTexture(Asset::GetTexture("Wall"));

    RigidbodyComponent* wall4Rigidbody = new RigidbodyComponent(wall4);
    wall4Rigidbody->SetMass(0.0f);

    BoxCollisionComponent* wall4PolyCollision = new BoxCollisionComponent(wall4);

    //FLOOR
    Actor* floor = new Actor();
    AddActor(floor);

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    //ROOF
    Actor* roof = new Actor();
    AddActor(roof);

    roof->SetLocation(Vec3(0.0f, 0.0f, 4.0f));
    roof->Rotate(Vec3(0.0f, 180.0f, 0.0f));

    MeshComponent* roofMeshComponent = new MeshComponent(roof);
    roofMeshComponent->SetMesh(Asset::GetMesh("Roof"));
    roofMeshComponent->AddTexture(Asset::GetTexture("Roof"));

}

