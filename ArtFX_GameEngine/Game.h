#pragma once
#include "Window.h"
#include "Renderer.h"
#include <string>
#include <vector>
#include "Scene.h"

class Game
{
public:    
    Game(const char* pTitle);
private:
    std::string mName = "hello world";

    Window* mWindow;
    Renderer* mRenderer;

    Scene hello = Scene(mRenderer);
    std::vector<Scene> mScenes = { hello };
    int CurrentScene = 0;

    bool mIsRunning = false;
    
    void Initialize();
    void Loop();
    void Render();
    void Update();
    void CheckInputs();
    void Close();
};
