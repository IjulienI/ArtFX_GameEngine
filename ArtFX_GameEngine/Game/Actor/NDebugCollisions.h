#pragma once
#include "Core/Class/Actor/Actor.h"

class NDebugCollisions : public Actor
{
    
public:    
    NDebugCollisions(Transform2D location, Scene& scene, ActorState state);
    ~NDebugCollisions() override = default;
    
public:
    void Start() override;
    void Update() override;
    void Destroy() override;
};
