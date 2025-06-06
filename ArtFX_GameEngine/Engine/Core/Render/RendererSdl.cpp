/**
 * @file RendererSdl.cpp
 * @brief Implementation of the RendererSdl class, which provides SDL-based rendering functionality.
 */

#include "RendererSdl.h"
#include "../../Debug/Log.h"
#include <SDL_image.h>	

#include "Component/SpriteComponent.h"
#include "Core/Class/Actor/Actor.h"
#include "Math/Maths.h"

/**
 * @brief Constructs a RendererSdl object and initializes the SDL renderer pointer to nullptr.
 */
RendererSdl::RendererSdl(): mSdlRenderer(nullptr)
{
}

/**
 * @brief Initializes the SDL renderer with the given window.
 * @param rWindow Reference to the window object.
 * @return True if initialization succeeded, false otherwise.
 */
bool RendererSdl::Initialize(Window& rWindow)
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

/**
 * @brief Begins the drawing process by clearing the screen.
 */
void RendererSdl::BeginDraw()
{
	SDL_SetRenderDrawColor(mSdlRenderer, 32, 32, 32, 255);
	SDL_RenderClear(mSdlRenderer);
}

/**
 * @brief Draws all registered objects.
 */
void RendererSdl::Draw()
{
	DrawSprites();
}

/**
 * @brief Ends the drawing process and presents the rendered frame.
 */
void RendererSdl::EndDraw()
{
	SDL_RenderPresent(mSdlRenderer);
}

/**
 * @brief Closes the renderer and releases resources.
 */
void RendererSdl::Close()
{
	SDL_DestroyRenderer(mSdlRenderer);
}

/**
 * @brief Draws a rectangle with the specified color.
 * @param rRect Rectangle to draw.
 * @param r Red color component.
 * @param g Green color component.
 * @param b Blue color component.
 * @param a Alpha color component (default is 255).
 */
void RendererSdl::DrawRect(Rectangle& rRect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(mSdlRenderer, r, g, b, a);
	SDL_Rect sdlRect = rRect.ToSdlRect();
	SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

/**
 * @brief Draws a sprite for a given actor using the specified texture and transformation.
 * @param actor Reference to the actor.
 * @param tex Reference to the texture.
 * @param rect Source rectangle for the texture.
 * @param pos Position to draw the sprite.
 * @param orientation Flip orientation for the sprite.
 */
void RendererSdl::DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation)
{
	SDL_Rect destinationRect;
	Transform transform = actor.GetTransform();
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
	   -Maths::ToDeg(transform.GetRotation().z),
	   nullptr,
	   static_cast<SDL_RendererFlip>(orientation));

	delete sourceSDL;

}

/**
 * @brief Draws all registered sprite components.
 */
void RendererSdl::DrawSprites()
{
	for(auto it : mSprites)
	{
		it->Draw(*this);
	}
}

/**
 * @brief Adds a sprite component to the renderer.
 * @param component Pointer to the sprite component.
 */
void RendererSdl::AddSprite(SpriteComponent* component)
{
	int spriteDrawOrder = component->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator sc;
	for(sc = mSprites.begin(); sc != mSprites.end(); ++sc)
	{
		if(spriteDrawOrder < (*sc)->GetDrawOrder()) break;
	}
	mSprites.insert(sc, component);
}

/**
 * @brief Removes a sprite component from the renderer.
 * @param component Pointer to the sprite component.
 */
void RendererSdl::RemoveSprite(SpriteComponent* component)
{
	std::vector<SpriteComponent*>::iterator sc;
	sc = std::find(mSprites.begin(), mSprites.end(), component);
	mSprites.erase(sc);
}

/**
 * @brief Gets the type of the renderer.
 * @return RendererType enum value.
 */
IRenderer::RendererType RendererSdl::GetType()
{
	return RendererType::SDL;
}

/**
 * @brief Converts the renderer to an SDL_Renderer pointer.
 * @return Pointer to the SDL_Renderer.
 */
SDL_Renderer* RendererSdl::ToSdlRenderer()
{
	return mSdlRenderer;
}
