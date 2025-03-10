#pragma once

#include <vector>
#include "Interface/IRenderer.h"

class SpriteComponent;

class RendererSdl : public IRenderer
{
private:
	SDL_Renderer* mSdlRenderer;

private:
	std::vector<SpriteComponent*> mSprites;
	
public:
	RendererSdl();
	RendererSdl(const RendererSdl&) = delete;
	RendererSdl& operator= (const RendererSdl&) = delete;

	virtual ~RendererSdl() override = default;

	bool Initialize(Window& rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;
	void Close() override;

	void DrawRect(Rectangle& rRect,Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) override;
	void DrawSprites() override;

public:
	void AddSprite(SpriteComponent* component);
	void RemoveSprite(SpriteComponent* component);

	RendererType GetType() override;

public:
	SDL_Renderer* ToSdlRenderer();
};
