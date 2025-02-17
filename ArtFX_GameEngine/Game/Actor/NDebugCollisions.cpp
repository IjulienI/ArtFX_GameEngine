#include "NDebugCollisions.h"

#include "Debug/Log.h"

NDebugCollisions::NDebugCollisions(Transform2D location, Scene& scene, ActorState state) : Actor(location, state)
{
    
}

void NDebugCollisions::Start()
{
    Actor::Start();
}

void NDebugCollisions::Update()
{
    Actor::Update();
    Log::Info(mScene.mRenderer ? "True" : "False");
}

void NDebugCollisions::Destroy()
{
    Actor::Destroy();
}
