#pragma once
#include "Renderer.h"
#include <string>

class Scene
{
private: 
	std::string mTitle;
	Renderer* mRenderer;
public:
	Scene(Renderer* pRenderer, std::string pTitle = "NoName");

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void OnInput(SDL_Event);
	virtual void Close();
};

