#include "PongScene.h"

#include "../../Engine/Debug/Log.h"
#include "../../Engine/Math/Time.h"
#include <algorithm>

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Math/Rectangle.h"
#include "Storage/Assets.h"

PongScene::PongScene(): Scene(nullptr, "Pong")
{
}

void PongScene::Start()
{
    mWindowSize = mCurrentWindow->GetDimensions();
    mInitialPaddleLoc = (mWindowSize.y / 2) - (mPaddleSize.y /2);
    mMaxPosY = mWindowSize.y - mPaddleSize.y;
    mPlayerRect = new Rectangle({mPaddleOffset,0.0f},{mPaddleSize.x,mPaddleSize.y});
    mEnemyRect = new Rectangle({mWindowSize.x - mPaddleOffset - mPaddleSize.x,0.0f},{mPaddleSize.x,mPaddleSize.y});
    mBallRect = new Rectangle({0.0f,0.0f},{ mBallSize,mBallSize});
    mBallBaseLoc = { (mWindowSize.x / 2.0f) - mBallSize / 2.0f, (mWindowSize.y / 2.0f) - mBallSize / 2.0f};
    mBallRect->position = mWindowSize / 2.0f;
    mBallSpeed = mBallBaseSpeed;
    ResetPaddleLoc();
    
    Asset::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    Actor* actor = new Actor();
    AddActor(actor);
    SpriteComponent* sprite =  new SpriteComponent(actor, Assets::GetTexture("ball"));
    actor->SetLocation(Vec2{500, 500});
}

void PongScene::Update()
{
    if(!mGameOn) return;
    PlayerUpdate();
    EnemyUpdate();
    BallUpdate();
    Collisions();
}

void PongScene::OnInput(SDL_Event sdl_event)
{
    //HandleInputs
    switch (sdl_event.type) {
    case SDL_KEYDOWN:
        if (sdl_event.key.keysym.sym == SDLK_UP)  mGoUp = true;
        if (sdl_event.key.keysym.sym == SDLK_DOWN)  mGoDown = true;
        if (sdl_event.key.keysym.sym == SDLK_SPACE) mGameOn = true;
        break;
    case SDL_KEYUP:
        if (sdl_event.key.keysym.sym == SDLK_UP)  mGoUp = false;
        if (sdl_event.key.keysym.sym == SDLK_DOWN)  mGoDown = false;
    default:
        break;
    }
}

void PongScene::Close() const
{
    Scene::Close();
}

void PongScene::PlayerUpdate()
{
    //////////////
    /// PLAYER ///
    //////////////
    
    //Apply Movements
    if(mGoUp) mPlayerRect->position.y -= mPlayerSpeed * Time::deltaTime;
    if(mGoDown) mPlayerRect->position.y += mPlayerSpeed * Time::deltaTime;

    //If touch screen corner, tp
    if(mPlayerRect->position.y < 5.0f) mPlayerRect->position.y = 5.0f;
    if(mPlayerRect->position.y > mMaxPosY -5.0f) mPlayerRect->position.y = mMaxPosY -5.0f;
}

void PongScene::BallUpdate()
{
    /////////////
    /// BALL ///
    ////////////
    
    //Apply Movements
    mBallRect->position += { (mBallSpeed * mBallVelocity.x) * Time::deltaTime, (mBallSpeed * mBallVelocity.y) * Time::deltaTime};

    //If touch screen x corners, add score and replay.
    //If touch screen y corners, reverse y Velocity and tp for prevent clipping
    if(mBallRect->position.x < 0.0f)
    {
        mBallRect->position = mBallBaseLoc;
        mBallVelocity.x *= -1.0f;
        mBallVelocity.y = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1))));
        AddScore(false);
        ResetPaddleLoc();
        mBallSpeed = mBallBaseSpeed;
        mGameOn = false;
    }
    else if(mBallRect->position.x > mWindowSize.x - mBallSize)
    {
        mBallRect->position = mBallBaseLoc;
        mBallVelocity.x *= -1.0f;
        mBallVelocity.y = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1))));
        AddScore(true);
        ResetPaddleLoc();
        mBallSpeed = mBallBaseSpeed;
        mGameOn = false;
    }
    if(mBallRect->position.y < 0.0f)
    {
        mBallRect->position.y= 0.0f;
        mBallVelocity.y *= -1.0f;
        mBallSpeed += 10.0f;
    }
    else if(mBallRect->position.y > mWindowSize.y - mBallSize)
    {
        mBallRect->position.y = mWindowSize.y - mBallSize;
        mBallVelocity.y *= -1.0f;
        mBallSpeed += 10.0f;
    }
}

void PongScene::EnemyUpdate()
{
    /////////////
    /// ENEMY ///
    /// /////////

    //Ai Logic
    float ballDist = (mEnemyRect->position.y + mPaddleSize.y / 2.0f) - mBallRect->position.y;
    
    if(ballDist < -25.0f) mEnemyVelocity = 1.0f;
    else if (ballDist > 25.0f) mEnemyVelocity = -1.0f;
    else mEnemyVelocity = 0.0f;

    //Apply Movements
    mEnemyRect->position.y += (mEnemyVelocity * mEnemySpeed) * Time::deltaTime;

    //If touch screen corner, tp
    if(mEnemyRect->position.y < 5.0f) mEnemyRect->position.y = 5.0f;
    if(mEnemyRect->position.y > mMaxPosY -5.0f) mEnemyRect->position.y = mMaxPosY -5.0f;
}

void PongScene::Collisions()
{
}

void PongScene::ResetPaddleLoc()
{
    mPlayerRect->position.y = mInitialPaddleLoc;
    mEnemyRect->position.y = mInitialPaddleLoc;
}

void PongScene::AddScore(bool bIsPlayer)
{    
    if(bIsPlayer)
    {
        mPlayerScore++;
        PrintScore();
        CheckWin(mPlayerScore, bIsPlayer);
    }    
    else{
        mEnemyScore++;
        PrintScore();
        CheckWin(mEnemyScore, bIsPlayer);
    }  
}

void PongScene::CheckWin(int score, bool bIsPlayer)
{
    if(score < mMaxScore) return;
    mPlayerScore = 0;
    mEnemyScore = 0;
    Log::Info(bIsPlayer? "\n Blue win !" : "Red win !");    
}

void PongScene::PrintScore()
{
    SDL_Log(" \n Blue Score : %i \n Red Score  : %i",mPlayerScore,mEnemyScore);
}
