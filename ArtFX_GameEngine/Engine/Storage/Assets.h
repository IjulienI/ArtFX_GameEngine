#pragma once
#include <map>
#include <string>
#include "../Core/Render/Texture.h"

class Assets
{
public:
    static std::map<std::string, Texture> mTextures;

    static Texture LoadTexture(RendererSdl& renderer, const std::string& filePath, const std::string& name);
    static Texture& GetTexture(const std::string& name);
    static void Clear();

private:
    Assets() = default;
    static Texture LoadTextureFromFile(RendererSdl& renderer, const std::string filePath);
};
