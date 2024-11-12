#pragma once
#include "Scene.h"

class PongScene : public Scene
{
private:
    float mPlayerPosY = 100;
    float mMaxPosY = 0;
    float mPaddleSpeed = 500.0f;
    Window* mCurrentWindow = nullptr;
    
public:
    PongScene();
    
    void Start() override;
    void Update() override;
    void Render() const override;
    void OnInput(SDL_Event) override;
    void Close() const override;

    void SetWindow(Window* pWindow);
};
