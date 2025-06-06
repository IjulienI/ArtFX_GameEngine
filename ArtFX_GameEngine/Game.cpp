/**
 * @file Game.cpp
 * @brief Implementation of the Game class, which manages the game engine lifecycle.
 */

#include "Game.h"
#include <iostream>

#include "Core/Physic/PhysicEngine.h"
#include "Core/Render/OpenGL/RendererGL.h"
#include "Debug/Log.h"
#include "Engine/Math/Time.h"
#include "Input/InputManager.h"

/**
 * @brief Constructs the Game class and initializes SDL.
 * @param pName Name of the game.
 * @param pScenes List of scenes in the game.
 * @param pLoadedScene Index of the default loaded scene.
 */
Game::Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene): mName(pName), mScenes(pScenes), mPhysicEngine(nullptr), mLoadedScene(pLoadedScene)
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

/**
 * @brief Initializes the game engine, sets up the window, renderer, and loads the default scene.
 */
void Game::Initialize()
{
    mWindow = new Window(1920,1080, mName);

    mRenderer = new RendererGL();

    if(mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        if(mScenes.size() == 1) mLoadedScene = 0;
        mScenes[mLoadedScene]->SetRenderer(mRenderer);
        mScenes[mLoadedScene]->SetWindow(mWindow);
        mPhysicEngine = &PhysicEngine::GetInstance();
        mScenes[mLoadedScene]->Load();
        mScenes[mLoadedScene]->Start();
        Loop();
    } 
}

/**
 * @brief Main loop of the game engine, handling updates, rendering, and inputs.
 */
void Game::Loop()
{
    mIsRunning = true;
    while(mIsRunning)
    {
        Time::ComputeDeltaTime();
        
        CheckInputs();

        Update();

        mPhysicEngine->Update();
        
        Render();
        
        Time::DelayTime();
    }
    Close();
}

/**
 * @brief Handles rendering of the current scene.
 */
void Game::Render()
{
    mRenderer->BeginDraw();

    mRenderer->Draw();
    mScenes[mLoadedScene]->Render();
    mRenderer->EndDraw();
}

/**
 * @brief Updates the logic of the current scene.
 */
void Game::Update()
{
    mScenes[mLoadedScene]->Update();
}

/**
 * @brief Checks user inputs and handles events.
 */
void Game::CheckInputs()
{
    if(!mIsRunning) return;

    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        //Log::Info("Input");        
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) mIsRunning = false;
            
            #ifdef _DEBUG
            if ( event.key.keysym.sym == SDLK_1) mScenes[mLoadedScene]->GetRenderer().SetDawType(DrawType::Unlit);
            if ( event.key.keysym.sym == SDLK_2) mScenes[mLoadedScene]->GetRenderer().SetDawType(DrawType::Wireframe);
            if ( event.key.keysym.sym == SDLK_3) mScenes[mLoadedScene]->GetRenderer().SetDawType(DrawType::Debug);
            if ( event.key.keysym.sym == SDLK_4) mScenes[mLoadedScene]->GetRenderer().SetDawType(DrawType::Collision);
            #endif
            
            break;
        default:            
            break;
        }
        
        InputManager::Instance().HandleInputs(event);
    }
}

/**
 * @brief Closes the game engine and releases resources.
 */
void Game::Close()
{
    mScenes[mLoadedScene]->Close();
    mWindow->Close();
    SDL_Quit();
}
