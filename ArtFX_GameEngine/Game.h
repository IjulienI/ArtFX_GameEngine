#pragma once
#include "Window.h"
#include "Renderer.h"
#include <string>
#include <vector>
#include "Scene.h"

class Game
{
public:    
    Game(std::string pName, std::vector<Scene*> pScenes, int pLoadedScene = 0);

    void Initialize();
    
private:
    std::string mName = "hello world";

    Window* mWindow;
    Renderer* mRenderer;

    std::vector<Scene*> mScenes;
    int mLoadedScene;

    bool mIsRunning = false;    
    
    void Loop();
    void Render();
    void Update();
    void CheckInputs();
    void Close();
};
