/**
 * @file Texture.cpp
 * @brief Implementation of the Texture class, which handles loading and managing textures for rendering.
 */

#include "Texture.h"

#include "RendererSdl.h"
#include "OpenGL/RendererGL.h"
#include "SDL.h"
#include "Debug/Log.h"

/**
 * @brief Constructs a Texture object and initializes its properties.
 */
Texture::Texture()
{
    
}

/**
 * @brief Loads a texture using SDL.
 * @param renderer Pointer to the SDL renderer.
 * @param filePath Path to the texture file.
 * @param surface SDL surface containing the texture data.
 * @return True if the texture was loaded successfully.
 */
bool Texture::LoadSdl(RendererSdl* renderer, const std::string& filePath, SDL_Surface* surface)
{
    //Create texture from surface
    mSdlTexture = SDL_CreateTextureFromSurface(renderer->ToSdlRenderer(), surface);
    SDL_FreeSurface(surface);
    if(!mSdlTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture :"+filePath);
        return false;
    }
    Log::Info("Loaded SDL texture : "+filePath);
    return true;
}

/**
 * @brief Loads a texture using OpenGL.
 * @param Renderer Pointer to the OpenGL renderer.
 * @param FileName Path to the texture file.
 * @param Surface SDL surface containing the texture data.
 * @return True if the texture was loaded successfully.
 */
bool Texture::LoadGl(RendererGL* Renderer, const std::string& FileName, SDL_Surface* Surface)
{
    int format = 0;
    if(Surface->format->format == SDL_PIXELFORMAT_RGB24)
    {
        format = GL_RGB;
    } else if (Surface->format->format == SDL_PIXELFORMAT_RGBA32)
    {
        format = GL_RGBA;
    }
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, Surface->pixels);
    SDL_FreeSurface(Surface);
    Log::Info("Loaded GL texture : "+FileName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
    return true;
}

/**
 * @brief Sets the texture as active for rendering.
 */
void Texture::SetActive() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

/**
 * @brief Loads a texture from a file using the specified renderer.
 * @param renderer Reference to the renderer.
 * @param filePath Path to the texture file.
 * @return True if the texture was loaded successfully.
 */
bool Texture::LoadTexture(IRenderer& renderer, const std::string& filePath)
{
    mFilePath = filePath;
    SDL_Surface* surface = IMG_Load(mFilePath.c_str());
    if(!surface)
    {
        Log::Error(LogType::Application, "Failed to load texture file : " + mFilePath);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    if(renderer.GetType() == IRenderer::RendererType::SDL)
    {
        return LoadSdl(dynamic_cast<RendererSdl*>(&renderer), filePath, surface);
    }
    return LoadGl(dynamic_cast<RendererGL*>(&renderer), filePath, surface);
}

/**
 * @brief Unloads the texture and releases resources.
 */
void Texture::unload()
{
    if(mSdlTexture) SDL_DestroyTexture(mSdlTexture);
    else glDeleteTextures(1, &mTextureID);

}

/**
 * @brief Updates the texture's width and height information.
 * @param width Reference to the width variable.
 * @param height Reference to the height variable.
 */
void Texture::UpdateInfo(int& width, int& height)
{
    width = mWidth;
    height = mHeight;
}

/**
 * @brief Gets the width of the texture.
 * @return Width of the texture.
 */
int Texture::GetWidht()
{
    return mWidth;
}

/**
 * @brief Gets the height of the texture.
 * @return Height of the texture.
 */
int Texture::GetHeight()
{
    return mHeight;
}

/**
 * @brief Gets the SDL texture object.
 * @return Pointer to the SDL texture object.
 */
SDL_Texture* Texture::GetSdlTexture()
{
    return mSdlTexture;
}
