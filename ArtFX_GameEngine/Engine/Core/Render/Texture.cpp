#include "Texture.h"

#include "RendererSdl.h"
#include "Debug/Log.h"

bool Texture::LoadTexture(RendererSdl& renderer, const std::string& filePath)
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

SDL_Texture* Texture::GetSdlTexture()
{
    return mTexture;
}
