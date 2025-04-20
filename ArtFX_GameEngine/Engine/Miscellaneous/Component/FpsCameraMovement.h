#pragma once
#include "Core/Class/Component/Component.h"
#include "Input/IInputListener.h"
#include "Math/Vec3.h"

class Camera;
class FpsCameraMovement : public Component, IInputListener
{
private:
    Camera* mCamera;
    Vec3 mVelocity;
    float mSpeed;
    int mMouseDeltaX, mMouseDeltaY;
    float mPitch, mYaw;

public:
    FpsCameraMovement(Camera* camera);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;
    void OnCall(SDL_Event& event) override;
    
};
