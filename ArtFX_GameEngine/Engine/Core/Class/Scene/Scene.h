#pragma once
#include "../../Render/RendererSdl.h"
#include <string>
#include <deque>

class Actor;

class Scene
{
public:
	static Scene* ActiveScene;
	
	IRenderer* mRenderer = nullptr;	
	Window* mCurrentWindow = nullptr;
	
protected: 
	std::string mTitle;
	std::deque<Actor*> mActors;
	std::deque<Actor*> mPendingActors;

private:
	bool mUpdatingActors;
	
public:
	Scene();
	Scene(RendererSdl* pRenderer, std::string pTitle = "NoName");
	virtual ~Scene();

	virtual void Start();
	virtual void Update();
	virtual void Close() const;
	
	virtual void Load();
	virtual void Unload();

	void SetRenderer(IRenderer* pRenderer);
	void SetWindow(Window* pWindow);

public:
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	void UpdateActors();

public:
	std::deque<Actor*> GetActors();
	IRenderer* GetRenderer();
};
