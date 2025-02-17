#include "Scene.h"

#include <algorithm>
#include "../../Class/Actor/Actor.h"
#include "Storage/Assets.h"

Scene* Scene::ActiveScene = nullptr;

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
		delete actor;
	}
	Assets::Clear();
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
	actor->AttachScene(*this);
	if(mUpdatingActors)
	{
		mPendingActors.push_back(actor);
	}
	else
	{
		mActors.push_back(actor);
		actor->Start();
	}
}

void Scene::RemoveActor(Actor* actor)
{
	auto it = std::find(mActors.begin(),mActors.end(),actor);
	if(it != mActors.end())
	{
		iter_swap(it, mActors.end() -1);
		mActors.pop_back();
	}
	it = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if(it != mPendingActors.end())
	{
		iter_swap(it, mPendingActors.end() -1);
		mPendingActors.pop_back();
	}	
}

void Scene::UpdateActors()
{
	mUpdatingActors = true;
	for(auto actor : mActors)
	{
		actor->Update();
	}
	mUpdatingActors = false;

	for(auto actor : mPendingActors)
	{
		mActors.push_back(actor);
	}
	mPendingActors.clear();
}

std::deque<Actor*> Scene::GetActors()
{
	return mActors;
}

Renderer* Scene::GetRenderer()
{
	return mRenderer;
}
