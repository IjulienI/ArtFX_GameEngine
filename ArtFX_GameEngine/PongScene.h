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
    int mMaxScore = 5;
    bool mGameOn = true;
    float mInitialPaddleLoc = 0.0f;
    float mOutlineScale = 2.0f;
    float mMiddleScreenSize = 5.0f;
    
    //Player
    Rectangle* mPlayerRect = nullptr;
    float mPlayerSpeed = 300.0f;
    bool mGoUp = false;
    bool mGoDown = false;
    int mPlayerScore = 0;

    //Enemy
    Rectangle* mEnemyRect = nullptr;
    float mEnemySpeed = 300.0f;
    float mEnemyVelocity = 0.0f;
    int mEnemyScore = 0;

    //Ball
    Rectangle* mBallRect = nullptr;
    Vec2 mBallVelocity = { -1.0f, -1.0f};
    float mBallBaseSpeed = 200.0f;
    float mBallSpeed = 0.0f;
    float mBallSize = 10.0f;
    Vec2 mBallBaseLoc = {0.0f, 0.0f};

    void PlayerUpdate();
    void BallUpdate();
    void EnemyUpdate();
    void Collisions();
    void ResetPaddleLoc();
    void AddScore(bool bIsPlayer);
    void CheckWin(int score, bool bIsPlayer);
    void PrintScore();
    
public:
    PongScene();

    void Start() override;
    void Update() override;
    void Render() const override;
    void OnInput(SDL_Event) override;
    void Close() const override;
};
