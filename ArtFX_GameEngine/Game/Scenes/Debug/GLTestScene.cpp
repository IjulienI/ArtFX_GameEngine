
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
    floorMeshComponent->SetMesh(Asset::GetMesh("Sand"));
    floorMeshComponent->AddTexture(Asset::GetTexture("Sand"));
    floorMeshComponent->GetMesh()->SetNoiseTexture(Asset::GetTexture("SandNoise"));
    

    mTessVertexShader.Load("SimpleTess.vert", ShaderType::VERTEX);
    mTessFragShader.Load("SimpleTess.frag", ShaderType::FRAGMENT);
    mTessControlShader.Load("SimpleTess.tesc", ShaderType::TESSELLATION_CONTROL);
    mTessEvalShader.Load("SimpleTess.tese", ShaderType::TESSELLATION_EVALUATION);

    mTessProgram.Compose({ &mTessVertexShader, &mTessFragShader, &mTessControlShader, &mTessEvalShader });
    floorMeshComponent->GetMesh()->SetShaderProgram(mTessProgram);
    
    floorMeshComponent->SetUseTessellation(true);
    floorMeshComponent->SetTessellationLevel(35);
    floorMeshComponent->SetDisplacementScale(7.0f);

    Actor* water = new Actor();
    AddActor(water);
    
    water->SetName("Water");

    water->SetLocation(Vec3(0.0f, 0.0f, 4.0f));

    MeshComponent* waterMeshComponent = new MeshComponent(water);
    waterMeshComponent->SetMesh(Asset::GetMesh("Water"));
    waterMeshComponent->AddTexture(Asset::GetTexture("VoronoiNoise"));
    waterMeshComponent->GetMesh()->SetNoiseTexture(Asset::GetTexture("VoronoiNoise"));

    mTessWaterFragShader.Load("WaterTess.frag", ShaderType::FRAGMENT);
    mTessWaterEvalShader.Load("WaterTess.tese", ShaderType::TESSELLATION_EVALUATION);

    mTessWaterProgram.Compose({ &mTessVertexShader, &mTessWaterFragShader, &mTessControlShader, &mTessWaterEvalShader });
    waterMeshComponent->GetMesh()->SetShaderProgram(mTessWaterProgram);
    waterMeshComponent->GetMesh()->GetShaderProgram().setFloat("uAmplitude", 0.12f);
    waterMeshComponent->GetMesh()->GetShaderProgram().setFloat("uFrequency", 1.5f);
    waterMeshComponent->GetMesh()->GetShaderProgram().setFloat("uSpeed", 0.8f);

    
    waterMeshComponent->GetMesh()->SetShaderProgram(mTessWaterProgram);
    waterMeshComponent->SetUseTessellation(true);
    waterMeshComponent->SetTessellationLevel(35);
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
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Sand.png", "Sand");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Jenga.png", "Jenga");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPin.png", "BowlingPin");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingBall.png", "BowlingBall");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Noises/SandNoise.png", "SandNoise");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Noises/VoronoiNoise.png", "VoronoiNoise");
    
    //Load Meshes
    Asset::LoadMesh("Box.obj", "Box");
    Asset::LoadMesh("Sand.obj", "Sand");
    Asset::LoadMesh("Water.obj", "Water");
    Asset::LoadMesh("monkey.obj", "monkey");
    Asset::LoadMesh("Jenga.obj", "Jenga");
    Asset::LoadMesh("Bowling/BowlingPin.obj", "BowlingPin");
    Asset::LoadMesh("Bowling/BowlingBall.obj", "BowlingBall");
}
