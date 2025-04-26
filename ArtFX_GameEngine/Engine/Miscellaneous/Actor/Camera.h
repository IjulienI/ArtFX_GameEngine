#pragma once
#include "Core/Class/Actor/Actor.h"

class FpsCameraMovement;

class Camera : public Actor
{
public:
    Camera();
    void Update() override;
    void UpdateActor() override;
    void Start() override;
    
};
