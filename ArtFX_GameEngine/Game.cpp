#include "Game.h"
#include <iostream>

Game::Game(const char* pTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }
    Initialize();
}

void Game::Initialize()
{
    mWindow = new Window(800,600, mName);

    mRenderer = new Renderer();

    if(mWindow->Open() && mRenderer->Initialize(*mWindow)) Loop();
}

void Game::Loop()
{
    mIsRunning = true;
    while(mIsRunning)
    {
        CheckInputs();
        Update();
        Render();
    }
    Close();
}

void Game::Render()
{
    mRenderer->BeginDraw();

    mScenes[CurrentScene].Render();

    mRenderer->EndDraw();
}

void Game::Update()
{
    mScenes[CurrentScene].Update();
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
        default:
            break;
        }
    }
    mScenes[CurrentScene].OnInput(event);
}

void Game::Close()
{
    mScenes[CurrentScene].Close();
    mWindow->Close();
    SDL_Quit();
}
