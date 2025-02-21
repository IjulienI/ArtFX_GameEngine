#pragma once

#include <vector>
#include "Window.h"

class Texture;
class Actor;
class SpriteComponent;
class Rectangle;

enum class Flip
{
	NONE = SDL_FLIP_NONE,
	HORIZONTAL = SDL_FLIP_HORIZONTAL,
	VERTICAL = SDL_FLIP_VERTICAL
};

class Renderer
{
private:
	SDL_Renderer* mSdlRenderer;

private:
	std::vector<SpriteComponent*> mSprites;
	
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void Draw();
	void EndDraw();
	void Close();

	void DrawRect(Rectangle& rRect,Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation);
	void DrawSprites();

public:
	void AddSprite(SpriteComponent* component);
	void RemoveSprite(SpriteComponent* component);

public:
	SDL_Renderer* ToSdlRenderer();
};
