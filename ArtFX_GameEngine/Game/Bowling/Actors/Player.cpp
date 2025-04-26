#include "Player.h"

#include <algorithm>

#include "Bowling/Component/BowlingController.h"
#include "Bowling/Manager/PinManager.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Debug/Log.h"
#include "Math/Time.h"
#include "Miscellaneous/Actor/Camera.h"

Player::Player() : Actor()
{
    //Set default values
    mClassName = "Player";
    mName = "Player_01";

    //Set Variables
    controller = new BowlingController(this);
    
    mCamera = reinterpret_cast<Camera*>(mScene->GetActors()[0]);


    //SpawnBowlingball
    mBowlingball = new Actor();
    mScene->AddActor(mBowlingball);

    mBowlingballMesh = new MeshComponent(mBowlingball);
    mBowlingballMesh->SetMesh(Asset::GetMesh("BowlingBall"));
    mBowlingballMesh->AddTexture(Asset::GetTexture("BowlingBall"));

    mBowlingBallForceDirArrow = new Actor();
    mScene->AddActor(mBowlingBallForceDirArrow);
    mBowlingBallForceDirArrow->SetScale(Vec3(1.0f,1.0f,mPower));

    MeshComponent* BallForceDirArrowMesh = new MeshComponent(mBowlingBallForceDirArrow);
    BallForceDirArrowMesh->SetMesh(Asset::GetMesh("RedArrow"));
    BallForceDirArrowMesh->AddTexture(Asset::GetTexture("ArrowTexture"));

    mBowlingBallRotationArrow = new Actor();
    mScene->AddActor(mBowlingBallRotationArrow);
    mBowlingBallRotationArrow->SetScale(Vec3(1.0f,1.0f,mPower / 2.0f));

    MeshComponent* BallRotationArrowMesh = new MeshComponent(mBowlingBallRotationArrow);
    BallRotationArrowMesh->SetMesh(Asset::GetMesh("YellowArrow"));
    BallRotationArrowMesh->AddTexture(Asset::GetTexture("ArrowTexture"));

    mCameraBasePos = mCamera->GetLocation();
    mCameraBaseRot = mCamera->GetRotation();
}

void Player::Shoot()
{
    if (mBowlingState != EBowlingState::PreShoot) return;

    mBowlingState = EBowlingState::Shoot;
    mBowlingballMesh->SetVisible(false);

    mBowlingBallForceDirArrow->GetComponent<MeshComponent>()->SetVisible(false);
    mBowlingBallRotationArrow->GetComponent<MeshComponent>()->SetVisible(false);
    
    mBowlingBallThrow = new Actor();
    mScene->AddActor(mBowlingBallThrow);

    mBowlingBallThrow->SetLocation(mBowlingball->GetLocation());
    mBowlingBallThrow->SetRotation(GetRotation());
    mBowlingBallThrow->Rotate(Vec3(0.0f,0.0f,-90.0f));

    MeshComponent* bowlingBallMeshComponent = new MeshComponent(mBowlingBallThrow);
    bowlingBallMeshComponent->SetMesh(Asset::GetMesh("BowlingBall"));
    bowlingBallMeshComponent->AddTexture(Asset::GetTexture("BowlingBall"));

    RigidbodyComponent* BowlingBallRb = new RigidbodyComponent(mBowlingBallThrow);
    BowlingBallRb->SetRestitution(0.0f);
    BowlingBallRb->SetFriction(0.15f);
    BowlingBallRb->SetMass(100.8f);

    SphereCollisionComponent* bowlingBallCollisionComponent = new SphereCollisionComponent(mBowlingBallThrow);

    Vec3 forward = Vec3::Transform(Vec3::unitX, mBowlingBallThrow->GetRotation());
    BowlingBallRb->ApplyImpulseAngular(((5.0f * -mRotationPower) * BowlingBallRb->GetMass()) * forward);
    BowlingBallRb->ApplyImpulse(((70.0f * mPower) * BowlingBallRb->GetMass()) * forward);

    mShootCount++;
}

void Player::Move(float movement)
{   
    AddLocation(Vec3(movement * Time::deltaTime, 0.0f, 0.0f));
    float loc = GetLocation().x;
    if (loc < -39.779f)
    {
        SetLocation(Vec3(-39.779f, GetLocation().y, GetLocation().z)); 
    }
    else if (loc > -36.180f)
    {
        SetLocation(Vec3(-36.180f, GetLocation().y, GetLocation().z));
    }
}

void Player::Turn(float rotation)
{
    float rot = rotation * Time::deltaTime;
    Rotate(Vec3(0.0f, 0.0f, rot));
    Vec3 forward = Vec3::Transform(Vec3::unitX, GetRotation());
    if (forward.y < -0.5f || forward.y > 0.5f)
    {
        Rotate(Vec3(0.0f, 0.0f, -rot));
    }
}

void Player::ChangePower(float power)
{
    mPower = std::clamp(mPower + power, 0.5f, 1.0f);
    mBowlingBallForceDirArrow->SetScale(Vec3(1.0f,1.0f,mPower));
    mBowlingBallRotationArrow->SetScale(Vec3(1.0f,1.0f,mPower / 2.0f));
}

void Player::ChangeRotation(float rotation)
{
    mRotationPower = std::clamp(mRotationPower + rotation, -1.0f, 1.0f);
    mBowlingBallRotationArrow->SetRotation(GetRotation());
    mBowlingBallRotationArrow->Rotate(Vec3(0.0f, 0.0f, 45 * mRotationPower));
}

void Player::Start()
{
    Actor::Start();
}

void Player::Update()
{
    Actor::Update();
    Vec3 pos = GetLocation();
    switch (mBowlingState)
    {
    case EBowlingState::Intro:
        break;
    case EBowlingState::PreShoot:
        mBowlingballMesh->SetVisible(true);
        mBowlingball->SetLocation(pos);
        mBowlingball->SetRotation(GetRotation());
        mBowlingBallForceDirArrow->SetLocation(Vec3(pos.x, pos.y, 0.01f));
        mBowlingBallForceDirArrow->SetRotation(GetRotation());
        mBowlingBallRotationArrow->SetLocation(Vec3(pos.x, pos.y, 0.02f));
        mPinExtractor->SetLocation(Vec3::Lerp(mPinExtractor->GetLocation(),
            Vec3(mPinExtractor->GetLocation().x, mPinExtractor->GetLocation().y, 1.3f), 0.03f));
        break;
    case EBowlingState::Shoot:        
        if (mBowlingBallThrow->GetLocation().y < 10.0f)
        {
            mCameraLeft = mBowlingBallThrow->GetLocation().x < -37.98f;
            ChangeState(EBowlingState::CameraOnPin);
        }
        break;
    case EBowlingState::CameraOnPin:
        mTimer += 1 * Time::deltaTime;
        if (mTimer > 2.0f)
        {
            ChangeState(EBowlingState::EndShoot);
        }
        break;
    case EBowlingState::EndShoot:
        mCamera->SetRotation(Quaternion::Lerp(mCamera->GetRotation(), mCameraBaseRot, 0.02f)); 
        mCamera->SetLocation(Vec3::Lerp(mCamera->GetLocation(), mCameraBasePos, 0.03f));
        mPinExtractor->SetLocation(Vec3::Lerp(mPinExtractor->GetLocation(),
            Vec3(mPinExtractor->GetLocation().x, mPinExtractor->GetLocation().y, 0.0f), 0.03f));
        if (mCamera->GetLocation().NearEquals(mCameraBasePos, 0.1f))
        {
            ChangeState(EBowlingState::Replacement);
        }
        break;
    case EBowlingState::Replacement:
        mTimer += 1 * Time::deltaTime;
        if (mTimer > 1.0f)
        {
            ChangeState(EBowlingState::PreShoot);
        }
        mBowlingBallThrow->Destroy();
        break;
    case EBowlingState::EndGame:
        break;
    }
}

void Player::ChangeState(EBowlingState newState)
{
    switch (newState)
    {
    case EBowlingState::Intro:
    case EBowlingState::PreShoot:
        mBowlingBallForceDirArrow->GetComponent<MeshComponent>()->SetVisible(true);
        mBowlingBallRotationArrow->GetComponent<MeshComponent>()->SetVisible(true);
        mBowlingball->SetLocation(GetLocation());
        break;
    case EBowlingState::Shoot:
        break;
    case EBowlingState::CameraOnPin:
        mPinManager->SetPinPhysisc(true);
        mTimer = 0.0f;
        mCamera->SetLocation(Vec3(mCameraLeft? -40.0f :-36.0f,10.0f,1.0f));
        mCamera->Rotate(Vec3(-5.0f,0.0f,mCameraLeft? 15.0f : -15.0f));
        break;
    case EBowlingState::EndShoot:
        break;
    case EBowlingState::Replacement:
        mTimer = 0.0f;
        mPinManager->SetPinPhysisc(false);
        if (mShootCount < 2)
        {
            if (mPinManager->CheckValidPin() >= 10)
            {
                mPinManager->ResetGame();
                mShootCount = 0;
                return;
            }
            mPinManager->ResetNoHittendPins();
        }
        else
        {
            mPinManager->ResetGame();
            mShootCount = 0;
        }
        break;
    case EBowlingState::EndGame:
        break;
    }

    mBowlingState = newState;
}

void Player::SetPinExtractor(Actor* pPinExtractor)
{
    mPinExtractor = pPinExtractor;
}

void Player::Destroy()
{
    Actor::Destroy();
}
