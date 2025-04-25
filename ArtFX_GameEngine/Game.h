#pragma once
#include "Engine/Core/Render/RendererSdl.h"
#include "Engine/Core/Render/Window.h"
#include <string>
#include <vector>

#include "Core/Physic/PhysicEngine.h"
#include "Engine/Core/Class/Scene/Scene.h"

class Game
{
public:    
    Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene = 0);

    void Initialize();
    
private:
    std::string mName = "XCore - DebugEngine";

    Window* mWindow;
    IRenderer* mRenderer;
    PhysicEngine* mPhysicEngine;

    std::vector<Scene*> mScenes;
    int mLoadedScene;

    bool mIsRunning = false;    
    
    void Loop();
    void Render();
    void Update();
    void CheckInputs();
    void Close();
};
