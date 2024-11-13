#include "PongScene.h"

#include "Time.h"

void PongScene::Start()
{
    mWindowSize = mCurrentWindow->GetDimensions();
    mMaxPosY = mWindowSize.y - mPaddleSize.y;
    mPlayerPos.x = mPaddleOffset;
    mEnemyPos.x = mWindowSize.x - mPaddleOffset - mPaddleSize.x;
}

void PongScene::Update()
{
    PlayerUpdate();
    BallUpdate();
    EnemyUpdate();
}

void PongScene::Render() const
{
    //Draw PlayerPaddle
    Rectangle playerPaddle = {mPlayerPos.x,mPlayerPos.y,mPaddleSize.x,mPaddleSize.y};
    mRenderer->DrawRect(playerPaddle,0,0,255);

    //Draw EnemyPaddle
    Rectangle enemyPaddle = {mEnemyPos.x,mEnemyPos.y,mPaddleSize.x,mPaddleSize.y};
    mRenderer->DrawRect(enemyPaddle,255,0,0);

    //Draw Ball
    Rectangle ball = {mBallPos.x,mBallPos.y,mBallSize,mBallSize};
    mRenderer->DrawRect(ball,255,255,0);
}

void PongScene::OnInput(SDL_Event sdl_event)
{
    switch (sdl_event.type) {
    case SDL_KEYDOWN:
        if (sdl_event.key.keysym.sym == SDLK_UP)  mGoUp = true;
        if (sdl_event.key.keysym.sym == SDLK_DOWN)  mGoDown = true;
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
    if(mGoUp) mPlayerPos.y -= mPlayerSpeed * Time::deltaTime;
    if(mGoDown) mPlayerPos.y += mPlayerSpeed * Time::deltaTime;

    //If touch screen corner, tp
    if(mPlayerPos.y < 5.0f) mPlayerPos.y = 5.0f;
    if(mPlayerPos.y > mMaxPosY -5.0f) mPlayerPos.y = mMaxPosY -5.0f;
}

void PongScene::BallUpdate()
{
    /////////////
    /// BALL ///
    ////////////

    //Apply Movements
    mBallPos += { (mBallSpeed * mBallVelocity.x) * Time::deltaTime, (mBallSpeed * mBallVelocity.y) * Time::deltaTime};

    //If touch screen corner, tp and reverse velocity
    if(mBallPos.x < 0.0f)
    {
        mBallPos.x = 0.0f;
        mBallVelocity.x *= -1.0f;
    }
    else if(mBallPos.x > mWindowSize.x - mBallSize)
    {
        mBallPos.x = mWindowSize.x - mBallSize;
        mBallVelocity.x *= -1.0f;
    }
    if(mBallPos.y < 0.0f)
    {
        mBallPos.y= 0.0f;
        mBallVelocity.y *= -1.0f;
    }
    else if(mBallPos.y > mWindowSize.y - mBallSize)
    {
        mBallPos.y = mWindowSize.y - mBallSize;
        mBallVelocity.y *= -1.0f;
    }
}

void PongScene::EnemyUpdate()
{
    /////////////
    /// ENEMY ///
    /// /////////

    //Ai Logic
    float ballDist = (mEnemyPos.y + mPaddleSize.y / 2.0f) - mBallPos.y;
    
    if(ballDist < -25.0f) mEnemyVelocity = 1.0f;
    else if (ballDist > 25.0f) mEnemyVelocity = -1.0f;
    else mEnemyVelocity = 0.0f;

    //Apply Movements
    mEnemyPos.y += (mEnemyVelocity * mEnemySpeed) * Time::deltaTime;

    //If touch screen corner, tp
    if(mEnemyPos.y < 5.0f) mEnemyPos.y = 5.0f;
    if(mEnemyPos.y > mMaxPosY -5.0f) mEnemyPos.y = mMaxPosY -5.0f;
}
