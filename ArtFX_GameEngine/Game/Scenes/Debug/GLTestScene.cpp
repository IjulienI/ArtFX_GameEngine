#include "GLTestScene.h"

#include "Actor/Skybox.h"
#include "Bowling/Manager/PinManager.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
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
    
    //SkyBox
    Skybox* skybox = new Skybox();
    AddActor(skybox);

    //Floor
    Actor* floor = new Actor();
    AddActor(floor);
    
    floor->SetName("Floor");

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));
    //floor->Rotate(Vec3(45.0f, 0.0f, 0.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* floorRigidbody = new RigidbodyComponent(floor);
    floorRigidbody->SetMass(0.0f);

    BoxCollisionComponent* floorPolyCollision = new BoxCollisionComponent(floor);

    PinManager* pinManager = new PinManager();
}

void GLTestScene::Update()
{
    Scene::Update();
    Log::Info("FPS : " + std::to_string( 1.0f / Time::deltaTime));
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
    //Load Textures
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Floor.png", "Floor");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPin.png", "BowlingPin");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Floor.obj", "Floor");
    Asset::LoadMesh("monkey.obj", "monkey");
    Asset::LoadMesh("Bowling/BowlingPin.obj", "BowlingPin");
}
