#include "NDebugCollisions.h"

#include "Core/Class/Scene/Scene.h"
#include "Core/Render/Asset.h"
#include "Debug/Log.h"

NDebugCollisions::NDebugCollisions(Transform2D location, Scene& scene, ActorState state) : Actor(location, state)
{
    
}

void NDebugCollisions::Start()
{
}

void NDebugCollisions::Update()
{
    Actor::Update();
}

void NDebugCollisions::Destroy()
{
    Actor::Destroy();
}
