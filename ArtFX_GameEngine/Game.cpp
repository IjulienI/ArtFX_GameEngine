#include "Game.h"
#include <iostream>

#include "Game/Scenes/PongScene.h"
#include "Engine/Math/Time.h"

Game::Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene): mName(pName), mScenes(pScenes), mLoadedScene(pLoadedScene)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }
}

void Game::Initialize()
{
    mWindow = new Window(800,600, mName);

    mRenderer = new Renderer();

    if(mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        if(mScenes.size() == 1) mLoadedScene = 0;
        mScenes[mLoadedScene]->SetRenderer(mRenderer);
        mScenes[mLoadedScene]->SetWindow(mWindow);
        mScenes[mLoadedScene]->Start();
        Loop();
    } 
}

void Game::Loop()
{
    mIsRunning = true;
    while(mIsRunning)
    {
        Time::ComputeDeltaTime();
        CheckInputs();
        Update();
        Render();
        Time::DelayTime();
    }
    Close();
}

void Game::Render()
{
    mRenderer->BeginDraw();

    mScenes[mLoadedScene]->Render();

    mRenderer->EndDraw();
}

void Game::Update()
{
    mScenes[mLoadedScene]->Update();
}

void Game::CheckInputs()
{
    if(!mIsRunning) return;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) mIsRunning = false;
            break;
        default:
            break;
        }
        mScenes[mLoadedScene]->OnInput(event);
    }    
}

void Game::Close()
{
    mScenes[mLoadedScene]->Close();
    mWindow->Close();
    SDL_Quit();
}
