#pragma once

#include <map>
#include "Texture.h"

class IRenderer;

class Asset
{
public:
    static std::map<std::string, Texture> mTextures;

    static Texture LoadTexture(IRenderer& renderer, const std::string& filePath, const std::string& name);
    static Texture& GetTexture(const std::string& name);
    static void Clear();

private:
    Asset() = default;
    static Texture LoadTextureFromFile(IRenderer& renderer, const std::string& filePath);
    
};
