#pragma once
#include <SDL.h>
#include "Vec2.h"
#include <string>

class Window
{
private:
    std::string mTitle;
    SDL_Window* mSdlWindow = nullptr;
    Vec2 mDimensions;
    
public:
    Window(int pWitdh, int pHeight, std::string pTitle);
    Window(const Window&);
    Window& operator=(const Window&) = delete;

    Vec2 GetDimensions() const { return mDimensions;}

    SDL_Window* GetSldWindow() const {return mSdlWindow;}
    
    bool Open();
    void Close();
    void Update();
};
