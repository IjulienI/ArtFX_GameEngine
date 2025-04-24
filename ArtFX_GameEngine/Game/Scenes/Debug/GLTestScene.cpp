#include "GLTestScene.h"

#include "Actor/Skybox.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/RigidbodyComponent.h"
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

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));
    //floor->Rotate(Vec3(45.0f, 0.0f, 0.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* floorRigidbody = new RigidbodyComponent(floor);
    floorRigidbody->SetMass(0.0f);

    BoxCollisionComponent* floorPolyCollision = new BoxCollisionComponent(floor);

    //DebugBox
    Actor* debugBox = new Actor();
    AddActor(debugBox);

    debugBox->SetLocation(Vec3(10.0f, 1.2f, 10.0f));

    MeshComponent* debugBoxMeshComponent = new MeshComponent(debugBox);
    debugBoxMeshComponent->SetMesh(Asset::GetMesh("monkey"));
    debugBoxMeshComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* debugBoxRigidbody = new RigidbodyComponent(debugBox);

    PolyCollisionComponent* debugBoxSphere = new PolyCollisionComponent(debugBox);

    Actor* debugBoxActor = new Actor();
    AddActor(debugBoxActor);

    debugBoxActor->SetLocation(Vec3(10.0f, 0.0f, 15.0f));
    debugBoxActor->Rotate(Vec3(45.0f, 0.0f, 0.0f));

    MeshComponent* debugBoxActorComponent = new MeshComponent(debugBoxActor);
    debugBoxActorComponent->SetMesh(Asset::GetMesh("monkey"));
    debugBoxActorComponent->AddTexture(Asset::GetTexture("Floor"));

    RigidbodyComponent* debugBoxActorRigidbody = new RigidbodyComponent(debugBoxActor);

    PolyCollisionComponent* debugBoxActorPolyCollision = new PolyCollisionComponent(debugBoxActor);

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
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Floor.obj", "Floor");
    Asset::LoadMesh("monkey.obj", "monkey");
}
