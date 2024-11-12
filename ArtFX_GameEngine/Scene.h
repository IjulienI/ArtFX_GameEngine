#pragma once
#include "Renderer.h"
#include <string>

class Scene
{
protected: 
	std::string mTitle;
	Renderer* mRenderer = nullptr;
public:
	Scene();
	Scene(Renderer* pRenderer, std::string pTitle = "NoName");

	virtual void Start();
	virtual void Update();
	virtual void Render() const;
	virtual void OnInput(SDL_Event);
	virtual void Close() const;

	void SetRenderer(Renderer* pRenderer);
};

