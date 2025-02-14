#pragma once
#include "../../Render/Renderer.h"
#include <string>
#include <vector>

class Actor;

class Scene
{
public:
	Renderer* mRenderer = nullptr;	
	Window* mCurrentWindow = nullptr;
	
protected: 
	std::string mTitle;
	std::vector<Actor*> mActors;
	
public:
	Scene();
	Scene(Renderer* pRenderer, std::string pTitle = "NoName");
	virtual ~Scene();

	virtual void Start();
	virtual void Update();
	virtual void Render() const;
	virtual void OnInput(SDL_Event);
	virtual void Close() const;

	void SetRenderer(Renderer* pRenderer);
	void SetWindow(Window* pWindow);

public:
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

public:
	std::vector<Actor*> GetActors();
};
