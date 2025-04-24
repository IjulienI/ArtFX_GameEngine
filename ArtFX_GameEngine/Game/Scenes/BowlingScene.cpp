#include "BowlingScene.h"

#include "Actor/Skybox.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"

BowlingScene::BowlingScene()
{
}

void BowlingScene::Start()
{
    Scene::Start();

    //SkyBox
    Skybox* skybox = new Skybox();
    AddActor(skybox);

    //BowlingRoom
    Actor* BowlingRoom = new Actor();
    AddActor(BowlingRoom);

    MeshComponent* bowlingRoomMeshComponent = new MeshComponent(BowlingRoom);
    bowlingRoomMeshComponent->SetMesh(Asset::GetMesh("BowlingRoom"));
    
    //BowlingPists
    for (int i = 0; i < PIST_AMOUNT; i++)
    {
        Actor* bowlingPist = new Actor();
        AddActor(bowlingPist);

        bowlingPist->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));

        MeshComponent* bowlingPistMeshComponent = new MeshComponent(bowlingPist);
        bowlingPistMeshComponent->SetMesh(Asset::GetMesh("BowlingPist"));
        bowlingPistMeshComponent->AddTexture(Asset::GetTexture("BowlingPist"));

        if (i == 6)
        {            
            // RigidbodyComponent* bowlingPistRigidbodyComponent = new RigidbodyComponent(bowlingPist);
            // bowlingPistRigidbodyComponent->SetMass(0.0f);
            //
            // PolyCollisionComponent* bowlingPistCollisionComponent = new PolyCollisionComponent(bowlingPist);
        }
    }

    Actor* floor = new Actor();
    AddActor(floor);

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));
    //floor->Rotate(Vec3(45.0f, 0.0f, 0.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* floorRigidbody = new RigidbodyComponent(floor);
    floorRigidbody->SetMass(0.0f);

    BoxCollisionComponent* floorPolyCollision = new BoxCollisionComponent(floor);

    //BowlingPins
    // Actor* bowlingPin = new Actor();
    // AddActor(bowlingPin);
    //
    // bowlingPin->SetLocation(Vec3(-37.98f, 10.0f, 1.0f));
    //
    // MeshComponent* bowlingPistMeshComponent = new MeshComponent(bowlingPin);
    // bowlingPistMeshComponent->SetMesh(Asset::GetMesh("BowlingPin"));
    // bowlingPistMeshComponent->AddTexture(Asset::GetTexture("BowlingPin"));
    //
    // RigidbodyComponent* bowlingPistRigidbodyComponent = new RigidbodyComponent(bowlingPin);
    // bowlingPistRigidbodyComponent->SetMass(0.0f);
    //
    // PolyCollisionComponent* bowlingPistCollisionComponent = new PolyCollisionComponent(bowlingPin);
}

void BowlingScene::Update()
{
    Scene::Update();
    Log::Info("FPS : " + std::to_string( 1.0f / Time::deltaTime));
}

void BowlingScene::Render()
{
    Scene::Render();
}

void BowlingScene::Close() const
{
    Scene::Close();
}

void BowlingScene::Load()
{
    Scene::Load();
    //Load Textures
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPist.png", "BowlingPist");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPin.png", "BowlingPin");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Floor.png", "Floor");
    
    //Load Meshes
    Asset::LoadMesh("Floor.obj", "Floor");
    Asset::LoadMesh("Bowling/BowlingPist.obj", "BowlingPist");
    Asset::LoadMesh("Bowling/BowlingPin.obj", "BowlingPin");
    Asset::LoadMesh("Bowling/BowlingRoom.obj", "BowlingRoom");
    Asset::LoadMesh("Bowling/Collision/BowlingPistCollisionFloor.obj", "BowlingPistCollisionFloor");
    Asset::LoadMesh("monkey.obj", "monkey");
}
