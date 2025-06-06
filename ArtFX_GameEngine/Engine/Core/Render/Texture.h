/**
 * @file Texture.h
 * @brief Declaration of the Texture class, which handles loading and managing textures for rendering.
 */

#pragma once
#include <string>
#include "SDL_image.h"

class IRenderer;
class RendererSdl;
class RendererGL;

/**
 * @class Texture
 * @brief Represents a texture used in rendering, supporting both SDL and OpenGL.
 */
class Texture
{
protected:
    /**
     * @brief File path of the texture.
     */
    std::string mFilePath;

    /**
     * @brief SDL texture object.
     */
    SDL_Texture* mSdlTexture;

    /**
     * @brief Width of the texture.
     */
    int mWidth;

    /**
     * @brief Height of the texture.
     */
    int mHeight;

    /**
     * @brief OpenGL texture ID.
     */
    unsigned int mTextureID;

    /**
     * @brief Loads a texture using SDL.
     * @param renderer Pointer to the SDL renderer.
     * @param filePath Path to the texture file.
     * @param surface SDL surface containing the texture data.
     * @return True if the texture was loaded successfully.
     */
    bool LoadSdl(RendererSdl* renderer, const std::string& filePath, SDL_Surface* surface);

    /**
     * @brief Loads a texture using OpenGL.
     * @param Renderer Pointer to the OpenGL renderer.
     * @param FileName Path to the texture file.
     * @param Surface SDL surface containing the texture data.
     * @return True if the texture was loaded successfully.
     */
    bool LoadGl(RendererGL* Renderer, const std::string& FileName, SDL_Surface* Surface);

public:
    /**
     * @brief Constructs a Texture object.
     */
    Texture();

    /**
     * @brief Destructor for Texture.
     */
    ~Texture() = default;

    /**
     * @brief Loads a texture from a file using the specified renderer.
     * @param renderer Reference to the renderer.
     * @param filePath Path to the texture file.
     * @return True if the texture was loaded successfully.
     */
    bool LoadTexture(IRenderer& renderer, const std::string& filePath);

    /**
     * @brief Unloads the texture and releases resources.
     */
    void unload();

    /**
     * @brief Sets the texture as active for rendering.
     */
    void SetActive() const;

    /**
     * @brief Updates the texture's width and height information.
     * @param width Reference to the width variable.
     * @param height Reference to the height variable.
     */
    void UpdateInfo(int& width, int& height);

public:
    /**
     * @brief Gets the width of the texture.
     * @return Width of the texture.
     */
    int GetWidht();

    /**
     * @brief Gets the height of the texture.
     * @return Height of the texture.
     */
    int GetHeight();

    /**
     * @brief Gets the SDL texture object.
     * @return Pointer to the SDL texture object.
     */
    SDL_Texture* GetSdlTexture();
};
