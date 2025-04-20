#pragma once
#include <SDL.h>
#include "../../Math/Vec2.h"
#include <string>

class Window
{
private:
    std::string mTitle;
    SDL_Window* mSdlWindow = nullptr;
    
public:
    static Vec2 Dimensions;
    
    Window(int pWitdh, int pHeight, std::string pTitle);
    Window(const Window&);
    Window& operator=(const Window&) = delete;   

    Vec2 GetDimensions() const { return Dimensions;}

    SDL_Window* GetSldWindow() const {return mSdlWindow;}
    
    bool Open();
    void Close();
    void Update();
};
