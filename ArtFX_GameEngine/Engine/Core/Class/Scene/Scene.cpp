#include "Scene.h"

#include <algorithm>

#include "../../Class/Actor/Actor.h"

Scene::Scene(): mTitle("")
{
}

Scene::Scene(Renderer* pRenderer, std::string pTitle): mRenderer(pRenderer), mTitle(pTitle)
{
}

Scene::~Scene()
{
	
}

void Scene::Start()
{
	for (Actor* actor : mActors)
	{
		actor->Start();
	}
}

void Scene::Update()
{
	for (Actor* actor : mActors)
	{
		actor->Update();
	}
}

void Scene::Render() const
{

}

void Scene::OnInput(SDL_Event) 
{
}

void Scene::Close() const
{
	for (Actor* actor : mActors)
	{
		actor->Destroy();
	}
}

void Scene::SetRenderer(Renderer* pRenderer)
{
	mRenderer = pRenderer;
}

void Scene::SetWindow(Window* pWindow)
{
	mCurrentWindow = pWindow;
}

void Scene::AddActor(Actor* actor)
{
	mActors.push_back(actor);
	actor->Start();
}

void Scene::RemoveActor(Actor* actor)
{
	auto it = std::find(mActors.begin(),mActors.end(),actor);
	if(it != mActors.end())
	{
		iter_swap(it, mActors.end() -1);
		mActors.pop_back();
	}
}

std::vector<Actor*> Scene::GetActors()
{
	return mActors;
}
