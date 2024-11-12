#include "Renderer.h"
#include "Log.h"

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
	return true;
}

void Renderer::BeginDraw()
{
	SDL_SetRenderDrawColor(mSdlRenderer, 120, 120, 255, 255);
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

void Renderer::DrawRect(Rectangle& rRect)
{
	SDL_SetRenderDrawColor(mSdlRenderer, 255, 255, 255, 255);
	SDL_Rect sdlRect = rRect.ToSdlRect();
	SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}
