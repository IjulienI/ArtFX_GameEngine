#pragma once
#include "Engine/Core/Render/RendererSdl.h"
#include "Engine/Core/Render/Window.h"
#include <string>
#include <vector>

#include "Core/Physic/PhysicEngine.h"
#include "Engine/Core/Class/Scene/Scene.h"

/**
 * @file Game.h
 * @brief Définition de la classe Game, qui gère le moteur de jeu.
 */

/**
 * @class Game
 * @brief Classe principale du moteur de jeu.
 */
class Game
{
public:    
    /**
     * @brief Constructeur de la classe Game.
     * @param pName Nom du jeu.
     * @param pScenes Liste des scènes du jeu.
     * @param pLoadedScene Indice de la scène chargée par défaut.
     */
    Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene = 0);

    /**
     * @brief Initialise le moteur de jeu.
     */
    void Initialize();
    
private:
    std::string mName = "XCore - DebugEngine";

    Window* mWindow;
    IRenderer* mRenderer;
    PhysicEngine* mPhysicEngine;

    std::vector<Scene*> mScenes;
    int mLoadedScene;

    bool mIsRunning = false;
    
    /**
     * @brief Boucle principale du moteur.
     */
    void Loop();

    void Render();
    void Update();
    void CheckInputs();

    /**
     * @brief Ferme le moteur et libère les ressources.
     */
    void Close();
};

