#include "Actor.h"

#include <algorithm>
#include "../../../Debug/Log.h"
#include "Core/Class/Scene/Scene.h"
#include "Math/Transform.h"


Actor::Actor(Transform location, ActorState state) : mTransform(location), mScene(Scene::ActiveScene), mActorState(state)
{
    Initialize();
}

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
        component->SetTransform(mTransform);
    }
}

void Actor::Update()
{
    for(Component* component : mComponents)
    {
        component->Update();
    }
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

Transform Actor::GetTransform()
{
    return mTransform;
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
