/**
 * @file Game.h
 * @brief Declaration of the Game class, which manages the game engine lifecycle.
 */

#pragma once
#include "Engine/Core/Render/RendererSdl.h"
#include "Engine/Core/Render/Window.h"
#include <string>
#include <vector>

#include "Core/Physic/PhysicEngine.h"
#include "Engine/Core/Class/Scene/Scene.h"

/**
 * @class Game
 * @brief Main class for the game engine.
 */
class Game
{
public:    
    /**
     * @brief Constructs the Game class.
     * @param pName Name of the game.
     * @param pScenes List of scenes in the game.
     * @param pLoadedScene Index of the default loaded scene.
     */
    Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene = 0);

    /**
     * @brief Initializes the game engine.
     */
    void Initialize();
    
private:
    /**
     * @brief Name of the game.
     */
    std::string mName = "XCore - DebugEngine";

    /**
     * @brief Pointer to the game window.
     */
    Window* mWindow;

    /**
     * @brief Pointer to the renderer used for rendering scenes.
     */
    IRenderer* mRenderer;

    /**
     * @brief Pointer to the physics engine.
     */
    PhysicEngine* mPhysicEngine;

    /**
     * @brief List of scenes in the game.
     */
    std::vector<Scene*> mScenes;

    /**
     * @brief Index of the currently loaded scene.
     */
    int mLoadedScene;

    /**
     * @brief Flag indicating whether the game engine is running.
     */
    bool mIsRunning = false;
    
    /**
     * @brief Main loop of the game engine.
     */
    void Loop();

    /**
     * @brief Handles rendering of the current scene.
     */
    void Render();

    /**
     * @brief Updates the logic of the current scene.
     */
    void Update();

    /**
     * @brief Checks user inputs and handles events.
     */
    void CheckInputs();

    /**
     * @brief Closes the game engine and releases resources.
     */
    void Close();
};
