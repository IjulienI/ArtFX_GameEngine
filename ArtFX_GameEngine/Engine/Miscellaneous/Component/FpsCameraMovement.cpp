#include "FpsCameraMovement.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/PolyCollisionComponent.h"
#include "Core/Physic/Component/RigidbodyComponent.h"
#include "Core/Physic/Component/SphereCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Debug/Log.h"
#include "Input/InputManager.h"
#include "Math/Time.h"

class SphereCollisionComponent;

FpsCameraMovement::FpsCameraMovement(Camera* camera) : Component(reinterpret_cast<Actor*>(camera)), mCamera(camera),
                                                       mVelocity(Vec3::zero), mSpeed(10.0f), mSprintSpeed(30.0f), mPitch(0.0f)
{
    FpsCameraMovement::OnStart();
}

void FpsCameraMovement::OnStart()
{
    InputManager& InputManager = InputManager::Instance();
    InputManager.BindTo(SDL_SCANCODE_W, this);
    InputManager.BindTo(SDL_SCANCODE_S, this);
    InputManager.BindTo(SDL_SCANCODE_A, this);
    InputManager.BindTo(SDL_SCANCODE_D, this);
    InputManager.BindTo(SDL_SCANCODE_Q, this);
    InputManager.BindTo(SDL_SCANCODE_E, this);
    InputManager.BindTo(SDL_SCANCODE_LSHIFT, this);
    InputManager.BindTo(SDL_SCANCODE_R, this);
    InputManager.BindTo(SDL_SCANCODE_T, this);
    
    Component::OnStart();
}

void FpsCameraMovement::Update()
{
    SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);
    
    const float sensitivity = 0.2f * Time::deltaTime;
    
    float yawDelta = static_cast<float>(mMouseDeltaX) * sensitivity;
    float pitchDelta = static_cast<float>(mMouseDeltaY) * sensitivity;
    
    mYaw += yawDelta;
    mPitch += pitchDelta;
    
    mPitch = Maths::Clamp(mPitch, -Maths::PI / 2.0f, Maths::PI / 2.0f);
    
    Quaternion yawQuat(Vec3::unitZ, mYaw); 
    Quaternion pitchQuat(Vec3::unitY, mPitch);
    
    Quaternion finalRotation = Quaternion::Concatenate(pitchQuat, yawQuat);
    
    mOwner->SetRotation(finalRotation);
    
    Vec3 cameraPos = mOwner->GetTransform().GetPosition();
    Vec3 forward = Vec3::Transform(Vec3::unitY, finalRotation);
    Vec3 target = cameraPos + forward * 100.0f;
    Vec3 up = Vec3::Transform(Vec3::unitZ, finalRotation);

    Matrix4Row view = Matrix4Row::CreateLookAt(cameraPos, target, up);
    Scene::ActiveScene->GetRenderer().SetViewMatrix(view);
    
    Vec3 newPosition = cameraPos
        + (mOwner->GetTransform().Right() * mVelocity.x
        + mOwner->GetTransform().Up() * mVelocity.y
        + mOwner->GetTransform().Forward() * mVelocity.z) * Time::deltaTime;
    mOwner->SetLocation(newPosition);
}

void FpsCameraMovement::OnEnd()
{
    Component::OnEnd();
}

void FpsCameraMovement::OnCall(SDL_Event& event)
{
    switch (event.key.keysym.scancode)
    {
    case SDL_SCANCODE_W:
        mVelocity.z = event.type == SDL_KEYDOWN? (mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_S:
        mVelocity.z = event.type == SDL_KEYDOWN? -(mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_A:
        mVelocity.x = event.type == SDL_KEYDOWN? -(mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_D:
        mVelocity.x = event.type == SDL_KEYDOWN? (mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_LSHIFT:
        mSprint = event.type == SDL_KEYDOWN;
        break;
    case SDL_SCANCODE_Q:
        mVelocity.y = event.type == SDL_KEYDOWN? (mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_E:
        mVelocity.y = event.type == SDL_KEYDOWN? -(mSprint? mSprintSpeed: mSpeed) : 0.0f;
        break;
    case SDL_SCANCODE_R:
        if (event.type == SDL_KEYUP)
        {
            Actor* debugBoxActor = new Actor();
            Scene::ActiveScene->AddActor(debugBoxActor);

            debugBoxActor->SetLocation(Vec3(0, 0, 1.0f));

            MeshComponent* debugBoxActorComponent = new MeshComponent(debugBoxActor);
            debugBoxActorComponent->SetMesh(Asset::GetMesh("monkey"));
            //debugBoxActorComponent->AddTexture(Asset::GetTexture("BowlingBall"));

            RigidbodyComponent* debugBoxActorRigidbody = new RigidbodyComponent(debugBoxActor);
            debugBoxActorRigidbody->SetMass(100.0f);
            debugBoxActorRigidbody->SetRestitution(0.2f);
            debugBoxActorRigidbody->SetFriction(0.05f);

            PolyCollisionComponent* debugBoxActorPolyCollision = new PolyCollisionComponent(debugBoxActor);

            //debugBoxActorRigidbody->ApplyImpulse(Vec3(0.0f, -55000.0f, 0.0f));
            //debugBoxActorRigidbody->ApplyImpulseAngular(Vec3(0.0f, 1500.0f, 0.0f));
        }        
        break;
    case SDL_SCANCODE_T:
        if (event.type == SDL_KEYUP)
        {
            Actor* debugBoxActor = new Actor();
            Scene::ActiveScene->AddActor(debugBoxActor);

            //debugBoxActor->SetScale(Vec3(10.0f, 10.0f, 10.0f));

            debugBoxActor->SetLocation(Vec3(0, 0, 1.0f));

            MeshComponent* debugBoxActorComponent = new MeshComponent(debugBoxActor);
            debugBoxActorComponent->SetMesh(Asset::GetMesh("BowlingBall"));
            debugBoxActorComponent->AddTexture(Asset::GetTexture("BowlingBall"));

            RigidbodyComponent* debugBoxActorRigidbody = new RigidbodyComponent(debugBoxActor);
            debugBoxActorRigidbody->SetMass(100.0f);
            debugBoxActorRigidbody->SetRestitution(0.2f);
            debugBoxActorRigidbody->SetFriction(0.05f);

            SphereCollisionComponent* debugBoxActorPolyCollision = new SphereCollisionComponent(debugBoxActor);

            //debugBoxActorRigidbody->ApplyImpulse(Vec3(0.0f, -55000.0f, 0.0f));
            //debugBoxActorRigidbody->ApplyImpulseAngular(Vec3(0.0f, 1500.0f, 0.0f));
        }        
        break;
    }
}
