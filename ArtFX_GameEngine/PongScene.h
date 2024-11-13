#pragma once
#include "Scene.h"

class PongScene : public Scene
{
private:
    //General
    Vec2 mWindowSize = {0.0f, 0.0f};
    
    Vec2 mPaddleSize = { 25.0f, 100.0f};    
    float mMaxPosY = 0.0f;
    float mPaddleOffset = 15.0f;
    
    //Player
    Vec2 mPlayerPos = {100.0f, 0.0f};
    float mPlayerSpeed = 500.0f;
    bool mGoUp = false;
    bool mGoDown = false;

    //Enemy
    Vec2 mEnemyPos = {100.0f, 0.0f};
    float mEnemySpeed = 200.0f;
    float mEnemyVelocity = 0.0f;

    //Ball
    Vec2 mBallPos = {0.0f, 0.0f};
    Vec2 mBallVelocity = { 1.0f, -1.0f};
    float mBallSpeed = 200.0f;
    float mBallSize = 10.0f;

    void PlayerUpdate();
    void BallUpdate();
    void EnemyUpdate();
    bool HandleCollision();
    
public:
    PongScene() = default;
    
    void Start() override;
    void Update() override;
    void Render() const override;
    void OnInput(SDL_Event) override;
    void Close() const override;
};
