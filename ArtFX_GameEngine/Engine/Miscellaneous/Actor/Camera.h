#pragma once
#include "Core/Class/Actor/Actor.h"

class FpsCameraMovement;

class Camera : public Actor
{
private:
    FpsCameraMovement* mCameraMovement;
public:
    Camera();
    void UpdateActor() override;
    
};
