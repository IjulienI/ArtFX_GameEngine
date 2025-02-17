#include "Assets.h"
#include <sstream>

#include "../Debug/Log.h"


std::map<std::string, Texture> Assets::mTextures = {};

Texture Assets::LoadTexture(Renderer& renderer, const std::string& filePath, const std::string& name)
{
    mTextures[name] = LoadTextureFromFile(renderer, filePath);
    return mTextures[name];
}

Texture& Assets::GetTexture(const std::string& name)
{
    if(mTextures.find(name) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture "<<name<<" does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[name];
}

void Assets::Clear()
{
    for(auto iter : mTextures)
    {
        iter.second.unload();
    }
    mTextures.clear();
}

Texture Assets::LoadTextureFromFile(Renderer& renderer, const std::string filePath)
{
    Texture texture;
    texture.LoadTexture(renderer, filePath);
    return texture;
}
