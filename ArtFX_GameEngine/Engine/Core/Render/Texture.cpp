#include "Texture.h"

#include <SDL_image.h>
#include <SDL_surface.h>

#include "Renderer.h"
#include "Debug/Log.h"

bool Texture::LoadTexture(Renderer& renderer, const std::string& filePath)
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

    mTexture = SDL_CreateTextureFromSurface(renderer.ToSdlRenderer(), surface);
    SDL_FreeSurface(surface);
    if(!mTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture : " + mFilePath);
        return false;
    }
    Log::Info("Loaded texture : " + mFilePath);
    return true;
}

void Texture::unload()
{
    if(mTexture)
    {
        SDL_DestroyTexture(mTexture);
    }
}

void Texture::UpdateInfo(int& width, int& height)
{
    width = mWidth;
    height = mHeight;
}

int Texture::GetWidht()
{
    return mWidth;
}

int Texture::GetHeight()
{
    return mHeight;
}
