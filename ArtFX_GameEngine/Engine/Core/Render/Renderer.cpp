#include "Renderer.h"

#include "../../Debug/Log.h"
#include <SDL_image.h>	

Renderer::Renderer(): mSdlRenderer(nullptr)
{
}

bool Renderer::Initialize(Window& rWindow)
{
	mSdlRenderer = SDL_CreateRenderer(rWindow.GetSldWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		Log::Error(LogType::Video, "Failed to create Renderer");
		return false;
	}
	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::Error(LogType::Video, "Unable to initialize SDL_Image");
		return false;
	}
	return true;
}

void Renderer::BeginDraw()
{
	SDL_SetRenderDrawColor(mSdlRenderer, 32, 32, 32, 255);
	SDL_RenderClear(mSdlRenderer);
}

void Renderer::EndDraw()
{
	SDL_RenderPresent(mSdlRenderer);
}

void Renderer::Close()
{
	SDL_DestroyRenderer(mSdlRenderer);
}

void Renderer::DrawRect(Rectangle& rRect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(mSdlRenderer, r, g, b, a);
	SDL_Rect sdlRect = rRect.ToSdlRect();
	SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

void Renderer::Draw()
{
}

void Renderer::AddSprite(SpriteComponent* component)
{
}

void Renderer::RemoveSprite(SpriteComponent* component)
{
}

SDL_Renderer* Renderer::ToSdlRenderer()
{
	return mSdlRenderer;
}
