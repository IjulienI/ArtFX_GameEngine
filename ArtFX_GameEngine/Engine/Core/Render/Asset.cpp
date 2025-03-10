#include "Asset.h"

#include <sstream>

#include "RendererSdl.h"
#include "Debug/Log.h"
#include "Interface/IRenderer.h"


std::map<std::string, Texture> Asset::mTextures = {};

Texture Asset::LoadTexture(IRenderer& renderer, const std::string& filePath, const std::string& name)
{
    mTextures[name] = LoadTextureFromFile(renderer, filePath);
    return mTextures[name];
}

Texture& Asset::GetTexture(const std::string& name)
{
    if(mTextures.find(name) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture "<<name<<" does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[name];
}

void Asset::Clear()
{
    for(auto iter : mTextures)
    {
        iter.second.unload();
    }
    mTextures.clear();
}

Texture Asset::LoadTextureFromFile(IRenderer& renderer, const std::string& filePath)
{
    Texture texture;
    texture.LoadTexture(renderer, filePath);
    return texture;
}
