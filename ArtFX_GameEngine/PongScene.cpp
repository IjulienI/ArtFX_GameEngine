#include "PongScene.h"

#include "Log.h"
#include "Time.h"

void PongScene::Start()
{
    mWindowSize = mCurrentWindow->GetDimensions();
    mMaxPosY = mWindowSize.y - mPaddleSize.y;
    mPlayerRect = new Rectangle{mPaddleOffset,0.0f,mPaddleSize.x,mPaddleSize.y};
    mEnemyRect = new Rectangle{mWindowSize.x - mPaddleOffset - mPaddleSize.x,0,0,0};
    mBallRect = new Rectangle{0.0f,0.0f, mBallSize,mBallSize};
}

void PongScene::Update()
{
    PlayerUpdate();
    BallUpdate();    
    EnemyUpdate();
    Collisions();
}

void PongScene::Render() const
{
    //Draw PlayerPaddle
    Rectangle playerPaddle = {mPlayerRect->position.x,mPlayerRect->position.y,mPaddleSize.x,mPaddleSize.y};
    mRenderer->DrawRect(playerPaddle,0,0,255);

    //Draw EnemyPaddle
    Rectangle enemyPaddle = {mEnemyRect->position.x,mEnemyRect->position.y,mPaddleSize.x,mPaddleSize.y};
    mRenderer->DrawRect(enemyPaddle,255,0,0);

    //Draw Ball 
    mRenderer->DrawRect(*mBallRect,255,255,0);
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
    ///
    //Apply Movements
    mBallRect->position += { (mBallSpeed * mBallVelocity.x) * Time::deltaTime, (mBallSpeed * mBallVelocity.y) * Time::deltaTime};
    //If touch screen corner, tp and reverse velocity
    if(mBallRect->position.x < 0.0f)
    {
        mBallRect->position.x = 0.0f;
        mBallVelocity.x *= -1.0f;
    }
    else if(mBallRect->position.x > mWindowSize.x - mBallSize)
    {
        mBallRect->position.x = mWindowSize.x - mBallSize;
        mBallVelocity.x *= -1.0f;
    }
    if(mBallRect->position.y < 0.0f)
    {
        mBallRect->position.y= 0.0f;
        mBallVelocity.y *= -1.0f;
    }
    else if(mBallRect->position.y > mWindowSize.y - mBallSize)
    {
        mBallRect->position.y = mWindowSize.y - mBallSize;
        mBallVelocity.y *= -1.0f;
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
    if(HandleCollision(mBallRect,mPlayerRect))
    {
        mBallVelocity.x *= -1.0f;
        mBallRect->position.x = mPlayerRect->position.x + mPlayerRect->dimensions.x;
    }
    if(HandleCollision(mBallRect,mEnemyRect))
    {
        mBallVelocity.x *= -1.0f;
        mBallRect->position.x = mEnemyRect->position.x;
    }
    Log::Info(HandleCollision(mBallRect,mEnemyRect) ? "Yes" : "No");
}

bool PongScene::HandleCollision(Rectangle* a, Rectangle* b)
{
    float xMinA =  a->position.x;
    float yMinA =  a->position.y;
    float xMaxA =  a->position.x + a->dimensions.x;
    float yMaxA =  a->position.y + a->dimensions.y;
    float xMinB =  b->position.x;
    float yMinB =  b->position.y;
    float xMaxB =  b->position.x + b->dimensions.x;
    float yMaxB =  b->position.y + b->dimensions.y;

    return(!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

PongScene::PongScene(): Scene()
{
}
