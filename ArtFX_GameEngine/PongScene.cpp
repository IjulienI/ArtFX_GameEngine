#include "PongScene.h"

#include "Time.h"

PongScene::PongScene()
{
}

void PongScene::Start()
{
    mMaxPosY = mCurrentWindow->GetDimensions().y - 100;
}

void PongScene::Update()
{
    if(mPlayerPosY < 5.0f) mPlayerPosY = 5.0f;
    if(mPlayerPosY > mMaxPosY -5.0f) mPlayerPosY = mMaxPosY -5.0f;
}

void PongScene::Render() const
{
    Rectangle playerPaddle = {25,mPlayerPosY,25,100};
    
    mRenderer->DrawRect(playerPaddle,0,0,0,255);
}

void PongScene::OnInput(SDL_Event sdl_event)
{
    switch (sdl_event.type) {
    case SDL_KEYDOWN:
        if(sdl_event.key.keysym.sym == SDLK_UP)
        {
            mPlayerPosY -= mPaddleSpeed * Time::deltaTime;
        }
        if(sdl_event.key.keysym.sym == SDLK_DOWN)
        {
            mPlayerPosY += mPaddleSpeed * Time::deltaTime;
        }        
        break;
    default:
        break;
    }
}

void PongScene::Close() const
{
    Scene::Close();
}

void PongScene::SetWindow(Window* pWindow)
{
    mCurrentWindow = pWindow;
}
