#pragma once
#include <string>

#include "SDL_image.h"

class RendererSdl;

class Texture
{
protected:
    std::string mFilePath;
    SDL_Texture* mTexture;
    int mWidth,mHeight;
    
public:
    bool LoadTexture(RendererSdl& renderer, const std::string& filePath);
    void unload();
    
    void UpdateInfo(int& width, int& height);

public:
    int GetWidht();
    int GetHeight();
    SDL_Texture* GetSdlTexture();
    
    
};
