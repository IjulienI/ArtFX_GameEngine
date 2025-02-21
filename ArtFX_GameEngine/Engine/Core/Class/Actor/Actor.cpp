#include "Actor.h"

#include <algorithm>
#include "../../../Debug/Log.h"
#include "Core/Class/Scene/Scene.h"


Actor::Actor(Transform2D location, ActorState state) : mTransform(location), mScene(Scene::ActiveScene), mActorState(state)
{
    Initialize();
}

Actor::Actor() : mTransform(Transform2D()), mScene(Scene::ActiveScene), mActorState(ActorState::Active)
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
    //work please <3
    mScene = &scene;
    //<3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 
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
    for(Component* component : mComponents)
    {
        component->Update();
    }
}

void Actor::Destroy()
{
    
}

Vec2 Actor::GetLocation()
{
    return mTransform.position;
}

float Actor::GetRotation()
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
    return mScene;
}

std::vector<Component*> Actor::GetComponents()
{
    return mComponents;
}

void Actor::SetLocation(Vec2 loc)
{
    mTransform.position = loc;
}
