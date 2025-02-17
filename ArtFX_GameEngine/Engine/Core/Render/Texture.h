#pragma once
#include <string>

class Renderer;
class SDL_Texture;

class Texture
{
protected:
    std::string mFilePath;
    SDL_Texture* mTexture;
    int mWidth,mHeight;
    
public:
    bool LoadTexture(Renderer& renderer, const std::string& filePath);
    void unload();
    
    void UpdateInfo(int& width, int& height);

public:
    int GetWidht();
    int GetHeight();
    
    
};
