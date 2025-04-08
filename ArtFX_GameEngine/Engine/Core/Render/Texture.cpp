#include "Texture.h"

#include "RendererSdl.h"
#include "OpenGL/RendererGL.h"
#include "SDL.h"
#include "Debug/Log.h"


Texture::Texture()
{
    
}

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

void Texture::SetActive() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);

}

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

void Texture::unload()
{
    if(mSdlTexture) SDL_DestroyTexture(mSdlTexture);
    else glDeleteTextures(1, &mTextureID);

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
    return mSdlTexture;
}
