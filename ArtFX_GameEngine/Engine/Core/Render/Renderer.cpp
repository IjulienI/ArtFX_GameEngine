#include "Renderer.h"
#include "../../Debug/Log.h"
#include <SDL_image.h>	

#include "Component/SpriteComponent.h"
#include "Core/Class/Actor/Actor.h"
#include "Math/Maths.h"
#include "Math/Rectangle.h"

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

void Renderer::Draw()
{
	DrawSprites();
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

void Renderer::DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation)
{
	SDL_Rect destinationRect;
	Transform2D transform = actor.GetTransform();
	destinationRect.w = static_cast<int>(static_cast<float>(tex.GetWidht()) * transform.GetScale().x);
	destinationRect.h = static_cast<int>(static_cast<float>(tex.GetWidht()) * transform.GetScale().y);
	destinationRect.x = static_cast<int>(transform.GetPosition().x - pos.x);
	destinationRect.y = static_cast<int>(transform.GetPosition().y - pos.y);

	SDL_Rect* sourceSDL = nullptr;
	if(rect != Rectangle::NullRect)
	{
		sourceSDL = new SDL_Rect{
			Maths::Round(rect.position.x),
			Maths::Round(rect.position.y),
			Maths::Round(rect.dimensions.x),
			Maths::Round(rect.dimensions.y)};
	}
	SDL_RenderCopyEx(mSdlRenderer,
	   tex.GetSdlTexture(),
	   sourceSDL,
	   &destinationRect,
	   -Maths::ToDeg(transform.GetRotation()),
	   nullptr,
	   SDL_FLIP_NONE);

	delete sourceSDL;

}

void Renderer::DrawSprites()
{
	for(auto it : mSprites)
	{
		it->Draw(*this);
	}
}

void Renderer::AddSprite(SpriteComponent* component)
{
	int spriteDrawOrder = component->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator sc;
	for(sc = mSprites.begin(); sc != mSprites.end(); ++sc)
	{
		if(spriteDrawOrder < (*sc)->GetDrawOrder()) break;
	}
	mSprites.insert(sc, component);
}

void Renderer::RemoveSprite(SpriteComponent* component)
{
	std::vector<SpriteComponent*>::iterator sc;
	sc = std::find(mSprites.begin(), mSprites.end(), component);
	mSprites.erase(sc);
}

SDL_Renderer* Renderer::ToSdlRenderer()
{
	return mSdlRenderer;
}
