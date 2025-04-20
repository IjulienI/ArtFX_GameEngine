#include "Actor.h"

#include <algorithm>
#include "../../../Debug/Log.h"
#include "Core/Class/Scene/Scene.h"
#include "Math/Transform.h"

Actor::Actor() : mScene(Scene::ActiveScene), mActorState(ActorState::Active), mTransform(Transform(this))
{
}

void Actor::Initialize()
{
    Log::Info("Actor Initialize");
}

void Actor::Start()
{
    
}

void Actor::AttachScene(Scene& scene)
{
    mScene = &scene;
}

void Actor::AddComponent(Component* component)
{
    mComponents.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
    auto it = std::find(mComponents.begin(), mComponents.end(), component);
    if(it != mComponents.end())
    {
        iter_swap(it, mComponents.end() - 1);
        mComponents.pop_back();
    }
}

void Actor::SetActive(ActorState state)
{
    mActorState = state;
}

void Actor::UpdateComponentsTransform()
{
    for(Component* component : mComponents)
    {
        component->OnUpdateWorldTransform();
    }
}

void Actor::Update()
{
    for(Component* component : mComponents)
    {
        component->Update();
    }
    UpdateActor();
    mTransform.ComputeWorldTransform();
}

void Actor::UpdateActor()
{
}

void Actor::Destroy()
{
    
}

Vec3 Actor::GetLocation()
{
    return mTransform.position;
}

Quaternion Actor::GetRotation()
{
    return mTransform.rotation;
}

Vec3 Actor::GetScale()
{
    return mTransform.scale;
}

Transform& Actor::GetTransform()
{
    return mTransform;
}

Matrix4Row Actor::GetWorldTransform()
{
    return mTransform.GetWorldTransform();
}

Scene* Actor::GetScene()
{
    return mScene;
}

std::vector<Component*> Actor::GetComponents()
{
    return mComponents;
}

void Actor::SetLocation(Vec3 loc)
{
    mTransform.position = loc;
}

void Actor::SetScale(Vec3 scale)
{
    mTransform.scale = scale;
}

void Actor::SetRotation(Quaternion rotation)
{
    mTransform.rotation = rotation;
}

void Actor::Rotate(Vec3 rotation)
{
    mTransform.Rotate(rotation);
}

void Actor::RotateX(float rotation)
{
    mTransform.RotateX(rotation);
}

void Actor::RotateY(float rotation)
{
    mTransform.RotateY(rotation);
}

void Actor::RotateZ(float rotation)
{
    mTransform.RotateZ(rotation);
}
