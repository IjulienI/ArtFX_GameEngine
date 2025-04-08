#pragma once
#include <string>

#include "SDL_image.h"

class IRenderer;
class RendererSdl;
class RendererGL;

class Texture
{
protected:
    std::string mFilePath;
    SDL_Texture* mSdlTexture;
    int mWidth,mHeight;
    unsigned int mTextureID;
    bool LoadSdl(RendererSdl* renderer, const std::string& filePath, SDL_Surface* surface);
    bool LoadGl(RendererGL* Renderer, const std::string& FileName, SDL_Surface* Surface);

public:
    Texture();
    ~Texture() = default;
    bool LoadTexture(IRenderer& renderer, const std::string& filePath);
    void unload();
    void SetActive() const;
    
    void UpdateInfo(int& width, int& height);

public:
    int GetWidht();
    int GetHeight();
    SDL_Texture* GetSdlTexture();
    
    
};
