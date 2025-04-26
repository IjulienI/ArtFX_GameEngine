#include "BowlingScene.h"

#include "Bowling/BowlingConstants.h"
#include "Bowling/Actors/Player.h"
#include "Bowling/Manager/PinManager.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"
#include "Miscellaneous/Component/FpsCameraMovement.h"

BowlingScene::BowlingScene()
{
}

static PinManager* pinManager;

void BowlingScene::Start()
{
    Scene::Start();

    //Spawn Bowling Pist    
    Actor* PlayerPinExtractor = new Actor();
    AddActor(PlayerPinExtractor);

    Actor* BowlingRoom = new Actor();
    AddActor(BowlingRoom);

    MeshComponent* bowlingRoomMeshComponent = new MeshComponent(BowlingRoom);
    bowlingRoomMeshComponent->SetMesh(Asset::GetMesh("BowlingRoom"));
    bowlingRoomMeshComponent->AddTexture(Asset::GetTexture("BowlingPist"));

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
            PlayerPinExtractor->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));

            MeshComponent* PinExtractorMeshComponent = new MeshComponent(PlayerPinExtractor);
            PinExtractorMeshComponent->SetMesh(Asset::GetMesh("PinExtractor"));
            PinExtractorMeshComponent->AddTexture(Asset::GetTexture("BowlingPist"));
            
            RigidbodyComponent* bowlingPistRigidbodyComponent = new RigidbodyComponent(bowlingPist);
            bowlingPistRigidbodyComponent->SetMass(0.0f);
            bowlingPistRigidbodyComponent->SetFriction(0.0f);
            
            BoxCollisionComponent* bowlingPistCollisionComponent = new BoxCollisionComponent(bowlingPist,
                Asset::GetMesh("BowlingPistCollisionFloor").GetBoundingBox());

            SetUpBoxCollisions(i);
        }
        else
        {
            Actor* PinExtractor = new Actor();
            AddActor(PinExtractor);

            PinExtractor->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));
            MeshComponent* PinExtractorMeshComponent = new MeshComponent(PinExtractor);
            PinExtractorMeshComponent->SetMesh(Asset::GetMesh("PinExtractor"));
            PinExtractorMeshComponent->AddTexture(Asset::GetTexture("BowlingPist"));
        }
    }

    //PinManager
    pinManager = new PinManager();

    //Set Camera Location
    mActors[0]->SetLocation(Vec3(-37.98f, 45.0f, 3.0f));
    mActors[0]->Rotate(Vec3(15.0f, 0.0f, -90.0f));

    //Player
    mPlayer = new Player();\
    AddActor(mPlayer);

    mPlayer->SetLocation(Vec3(-37.98f, 38.0f, 1.0f));
    mPlayer->SetPinExtractor(PlayerPinExtractor);
    mPlayer->SetPinManger(pinManager);
     
}

void BowlingScene::Update()
{
    Scene::Update();
}

void BowlingScene::Render()
{
    Scene::Render();
}

void BowlingScene::Close() const
{
    Scene::Close();
}

void BowlingScene::SetUpBoxCollisions(int i )
{
    Actor* BowlingWallLeft = new Actor();
    AddActor(BowlingWallLeft);

    BowlingWallLeft->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));
    
    MeshComponent* bowlingWallLeftMeshComponent = new MeshComponent(BowlingWallLeft);
    bowlingWallLeftMeshComponent->SetMesh(Asset::GetMesh("BowlingWallLeftCollision"));
    bowlingWallLeftMeshComponent->SetVisible(false);

    RigidbodyComponent* bowlingWallLeftRigidbodyComponent = new RigidbodyComponent(BowlingWallLeft);
    bowlingWallLeftRigidbodyComponent->SetMass(0.0f);
    bowlingWallLeftRigidbodyComponent->SetFriction(0.0f);

    BoxCollisionComponent* bowlingWallLeftCollisionComponent = new BoxCollisionComponent(BowlingWallLeft);

    Actor* BowlingWallRight = new Actor();
    AddActor(BowlingWallRight);

    BowlingWallRight->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));

    MeshComponent* bowlingWallRightMeshComponent = new MeshComponent(BowlingWallRight);
    bowlingWallRightMeshComponent->SetMesh(Asset::GetMesh("BowlingWallRightCollision"));
    bowlingWallRightMeshComponent->SetVisible(false);
    
    RigidbodyComponent* bowlingWallRightRigidbodyComponent = new RigidbodyComponent(BowlingWallRight);
    bowlingWallRightRigidbodyComponent->SetMass(0.0f);
    bowlingWallRightRigidbodyComponent->SetFriction(0.0f);

    BoxCollisionComponent* bowlingWallRightCollisionComponent = new BoxCollisionComponent(BowlingWallRight);

    Actor* BowlingDown = new Actor();
    AddActor(BowlingDown);

    BowlingDown->SetLocation(Vec3(-PIST_OFFSET * i, 0.0f, 0.0f));

    MeshComponent* bowlingDownMeshComponent = new MeshComponent(BowlingDown);
    bowlingDownMeshComponent->SetMesh(Asset::GetMesh("BowlingDownCollision"));
    bowlingDownMeshComponent->SetVisible(false);

    RigidbodyComponent* bowlingDownRigidbodyComponent = new RigidbodyComponent(BowlingDown);
    bowlingDownRigidbodyComponent->SetMass(0.0f);
    bowlingDownRigidbodyComponent->SetFriction(0.0f);

    BoxCollisionComponent* bowlingDowntCollisionComponent = new BoxCollisionComponent(BowlingDown);
}

void BowlingScene::Load()
{
    Scene::Load();
    //Load Textures
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPist.png", "BowlingPist");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingPin.png", "BowlingPin");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/BowlingBall.png", "BowlingBall");
    Asset::LoadTexture(*mRenderer, "Resources/Textures/Bowling/ArrowTexture.png", "ArrowTexture");
    
    //Load Meshes
    Asset::LoadMesh("Bowling/BowlingPist.obj", "BowlingPist");
    Asset::LoadMesh("Bowling/BowlingPin.obj", "BowlingPin");
    Asset::LoadMesh("Bowling/BowlingRoom.obj", "BowlingRoom");
    Asset::LoadMesh("Bowling/BowlingBall.obj", "BowlingBall");
    Asset::LoadMesh("Bowling/YellowArroy.obj", "YellowArrow");
    Asset::LoadMesh("Bowling/RedArroy.obj", "RedArrow");
    Asset::LoadMesh("Bowling/PinExtractor.obj", "PinExtractor");
    
    //Collisions
    Asset::LoadMesh("Bowling/Collision/BowlingPistCollisionFloor.obj", "BowlingPistCollisionFloor");
    Asset::LoadMesh("Bowling/Collision/BowlingWallLeftCollision.obj", "BowlingWallLeftCollision");
    Asset::LoadMesh("Bowling/Collision/BowlingWallRightCollision.obj", "BowlingWallRightCollision");
    Asset::LoadMesh("Bowling/Collision/BowlingDownCollision.obj", "BowlingDownCollision");
    Asset::LoadMesh("Bowling/Collision/BowlingBackCollider1.obj", "BowlingBackCollider1");
    Asset::LoadMesh("Bowling/Collision/BowlingBackCollider2.obj", "BowlingBackCollider2");
}
