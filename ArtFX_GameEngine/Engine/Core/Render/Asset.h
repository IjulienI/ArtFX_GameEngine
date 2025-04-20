#pragma once

#include <map>
#include "Texture.h"
#include "Core/Class/Mesh/Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION

class IRenderer;

class Asset
{
public:
    static std::map<std::string, Texture> mTextures;
    static std::map<std::string, Mesh> mMeshes;

    static Texture LoadTexture(IRenderer& renderer, const std::string& filePath, const std::string& name);
    static Texture& GetTexture(const std::string& name);
    static Mesh LoadMesh(const std::string& pFileName, const std::string& pName);
    static Mesh& GetMesh(const std::string& pName);
    static void Clear();

private:
    Asset() = default;
    static Texture LoadTextureFromFile(IRenderer& renderer, const std::string& filePath);
    static Mesh LoadMeshFromFile(const std::string& pFileName);
    
};
