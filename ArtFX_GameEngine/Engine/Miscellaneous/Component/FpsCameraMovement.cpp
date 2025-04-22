#include "FpsCameraMovement.h"

#include "Core/Class/Actor/Actor.h"
#include "Debug/Log.h"
#include "Input/InputManager.h"
#include "Math/Time.h"

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
    
    Component::OnStart();
}

void FpsCameraMovement::Update()
{
    SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);

    Quaternion newRotation = mOwner->GetTransform().GetRotation();

    float yawAngle = static_cast<float>(mMouseDeltaX) * 0.2f * Time::deltaTime;
    Vec3 up = Vec3::Transform(Vec3::unitZ, newRotation);
    Quaternion increment(up, yawAngle);
    newRotation = Quaternion::Concatenate(newRotation, increment);
    mOwner->SetRotation(newRotation);

    Vec3 cameraPos = mOwner->GetTransform().GetPosition();
    mPitch += static_cast<float>(mMouseDeltaY) * 0.2f * Time::deltaTime;
    mPitch = Maths::Clamp(mPitch, -Maths::PI/2, Maths::PI/2);
    Quaternion q(mOwner->GetTransform().Right(), mPitch);
    Vec3 forward = Vec3::Transform(mOwner->GetTransform().Forward(), q);
    Vec3 target = cameraPos + forward * 100.0f;
    up = Vec3::Transform(Vec3::unitZ, q);
    
    Matrix4Row view = Matrix4Row::CreateLookAt(cameraPos, target, up);
    Scene::ActiveScene->GetRenderer().SetViewMatrix(view);
    
    Vec3 newPosition = cameraPos
    + (mOwner->GetTransform().Right() * mVelocity.x
    + mOwner->GetTransform().Up() * mVelocity.y
    + mOwner->GetTransform().Forward() * mVelocity.z ) * Time::deltaTime;
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
    default:
        Log::Warning(LogType::Input, "Unknown event type");
        break;
    }
}
