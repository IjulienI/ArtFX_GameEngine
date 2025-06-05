#pragma once
#include "../../Render/RendererSdl.h"
#include <string>
#include <deque>

class Camera;
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
	Camera* mCamera;

private:
	bool mUpdatingActors;
	
public:
	Scene();
	virtual ~Scene();

	virtual void Start();
	virtual void Update();
	virtual void Render();
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
	IRenderer& GetRenderer();
	
	Actor* GetActorOfClass(std::string pClass, bool& pValid, int pIndex = 0) const;
	std::vector<Actor*> GetActorsOfClass(std::string pClass, bool& pValid) const;

	Actor* GetActorByName(std::string pName, bool& pValid, int pIndex = 0) const;
	std::vector<Actor*> GetActorsByName(std::string pName, bool& pValid) const;
};
