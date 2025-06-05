
#include "GLTestScene.h"

#include "Actor/Skybox.h"
#include "Bowling/Manager/PinManager.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Force.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

GLTestScene::GLTestScene()
{
}

void GLTestScene::Start()
{
    Scene::Start();

    FpsCameraMovement* cameraMovement = new FpsCameraMovement(reinterpret_cast<Camera*>(mActors[0]));
    mActors[0]->SetLocation(Vec3(-50.0f, 0.0f, 5.0f));
    
    //SkyBox
    Skybox* skybox = new Skybox();
    AddActor(skybox);

    //Floor
    Actor* floor = new Actor();
    AddActor(floor);
    
    floor->SetName("Floor");

    floor->SetLocation(Vec3(0.0f, 0.0f, -10.0f));

    MeshComponent* floorMeshComponent = new MeshComponent(floor);
    floorMeshComponent->SetMesh(Asset::GetMesh("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Floor"));
    floorMeshComponent->AddTexture(Asset::GetTexture("VoronoiNoise"));
    

    mTessVertexShader.Load("SimpleTess.vert", ShaderType::VERTEX);
    mTessFragShader.Load("SimpleTess.frag", ShaderType::FRAGMENT);
    mTessControlShader.Load("SimpleTess.tesc", ShaderType::TESSELLATION_CONTROL);
    mTessEvalShader.Load("SimpleTess.tese", ShaderType::TESSELLATION_EVALUATION);

    mTessProgram.Compose({ &mTessVertexShader, &mTessFragShader, &mTessControlShader, &mTessEvalShader });
    floorMeshComponent->GetMesh()->SetShaderProgram(mTessProgram);
    floorMeshComponent->SetUseTessellation(true);
    floorMeshComponent->SetTessellationLevel(6);

    

    RigidbodyComponent* floorRigidbody = new RigidbodyComponent(floor);
    floorRigidbody->SetMass(0.0f);

    BoxCollisionComponent* floorPolyCollision = new BoxCollisionComponent(floor);
    
    for (int level = 0; level < 2; ++level)
    {
        for (int row = 0; row < 2; ++row)
        {
            for (int col = 0; col < 2; ++col)
            {
                Actor* wallBlock = new Actor();
                AddActor(wallBlock);
                
                MeshComponent* wallMeshComponent = new MeshComponent(wallBlock);
                wallMeshComponent->SetMesh(Asset::GetMesh("Box"));
                wallMeshComponent->AddTexture(Asset::GetTexture("Jenga"));

                RigidbodyComponent* wallRigidbody = new RigidbodyComponent(wallBlock);
                wallRigidbody->SetMass(100.6f);
                wallRigidbody->SetFriction(1.0f);
                wallRigidbody->SetRestitution(0.0f);

                BoxCollisionComponent* collision = new BoxCollisionComponent(wallBlock);
                
                Box box = wallMeshComponent->GetMesh()->GetBoundingBox();
                float blockWidth = box.max.x - box.min.x;
                float blockHeight = box.max.y - box.min.y;
                float blockLength = box.max.z - box.min.z;
                
                float xOffset = col * blockWidth;
                float yOffset = level * blockHeight;
                float zOffset = row * blockLength;

                Vec3 position(xOffset, yOffset, zOffset);
                wallBlock->SetLocation(position);
            }
        }
    }
}

void GLTestScene::Update()
{
    Scene::Update();
    //Log::Info("FPS : " + std::to_string( 1.0f / Time::deltaTime));
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
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Jenga.png", "Jenga");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPin.png", "BowlingPin");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingBall.png", "BowlingBall");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Noises/VoronoiNoise.png", "VoronoiNoise");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Floor.obj", "Floor");
    Asset::LoadMesh("monkey.obj", "monkey");
    Asset::LoadMesh("Jenga.obj", "Jenga");
    Asset::LoadMesh("Bowling/BowlingPin.obj", "BowlingPin");
    Asset::LoadMesh("Bowling/BowlingBall.obj", "BowlingBall");
}
