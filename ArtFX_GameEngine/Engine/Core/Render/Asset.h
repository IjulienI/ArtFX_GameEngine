/**
 * @file Asset.h
 * @brief Declaration of the Asset class, which manages textures and meshes for rendering.
 */

#pragma once

#include <map>
#include "Texture.h"
#include "Core/Class/Mesh/Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION

class IRenderer;

/**
 * @class Asset
 * @brief Static class for managing textures and meshes in the rendering system.
 */
class Asset
{
public:
    /**
     * @brief Map of loaded textures, indexed by name.
     */
    static std::map<std::string, Texture> mTextures;

    /**
     * @brief Map of loaded meshes, indexed by name.
     */
    static std::map<std::string, Mesh> mMeshes;

    /**
     * @brief Loads a texture from a file and stores it in the asset manager.
     * @param renderer Reference to the renderer.
     * @param filePath Path to the texture file.
     * @param name Name to associate with the loaded texture.
     * @return The loaded texture.
     */
    static Texture LoadTexture(IRenderer& renderer, const std::string& filePath, const std::string& name);

    /**
     * @brief Retrieves a texture by name.
     * @param name Name of the texture.
     * @return Reference to the texture.
     */
    static Texture& GetTexture(const std::string& name);

    /**
     * @brief Loads a mesh from a file and stores it in the asset manager.
     * @param pFileName Path to the mesh file.
     * @param pName Name to associate with the loaded mesh.
     * @return The loaded mesh.
     */
    static Mesh LoadMesh(const std::string& pFileName, const std::string& pName);

    /**
     * @brief Retrieves a mesh by name.
     * @param pName Name of the mesh.
     * @return Reference to the mesh.
     */
    static Mesh& GetMesh(const std::string& pName);

    /**
     * @brief Clears all loaded assets from the asset manager.
     */
    static void Clear();

private:
    /**
     * @brief Private constructor to prevent instantiation.
     */
    Asset() = default;

    /**
     * @brief Loads a texture from a file.
     * @param renderer Reference to the renderer.
     * @param filePath Path to the texture file.
     * @return The loaded texture.
     */
    static Texture LoadTextureFromFile(IRenderer& renderer, const std::string& filePath);

    /**
     * @brief Loads a mesh from a file.
     * @param pFileName Path to the mesh file.
     * @return The loaded mesh.
     */
    static Mesh LoadMeshFromFile(const std::string& pFileName);
};
