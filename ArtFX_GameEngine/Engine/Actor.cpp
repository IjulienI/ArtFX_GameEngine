#include "Actor.h"

#include <algorithm>
#include "../Log.h"

Actor::Actor(Transform2D location, Scene& scene, ActorState state) : mTransform(location), mScene(scene), mActorState(state)
{
    Initialize();
}

void Actor::Initialize()
{
    Log::Info("Actor Initialize");
}

void Actor::Start()
{
    
}

void Actor::AttachScene(const Scene& scene)
{
    mScene = scene;
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

void Actor::Update()
{
    
}

void Actor::Destroy()
{
    
}

Vec2 Actor::GetLocation()
{
    return mTransform.position;
}

Vec2 Actor::GetRotation()
{
    return mTransform.rotation;
}

Vec2 Actor::GetScale()
{
    return mTransform.scale;
}

Transform2D Actor::GetTransform()
{
    return mTransform;
}

Scene* Actor::GetScene()
{
    return &mScene;
}

std::vector<Component*> Actor::GetComponents()
{
    return mComponents;
}
