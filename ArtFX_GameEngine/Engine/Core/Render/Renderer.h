#pragma once
#include "../../Math/Rectangle.h"
#include "Window.h"

class SpriteComponent;

enum class Flip
{
	None,
};

class Renderer
{
private:
	SDL_Renderer* mSdlRenderer;
	
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void DrawRect(Rectangle& rRect,Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void Draw();

public:
	void AddSprite(SpriteComponent* component);
	void RemoveSprite(SpriteComponent* component);

public:
	SDL_Renderer* ToSdlRenderer();
};
