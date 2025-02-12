#include "Scene.h"
#include <iostream>

#include "Engine/Actor.h"

Scene::Scene(): mTitle("")
{
}

Scene::Scene(Renderer* pRenderer, std::string pTitle): mRenderer(pRenderer), mTitle(pTitle)
{
}

void Scene::Start()
{
}

void Scene::Update()
{
}

void Scene::Render() const
{
}

void Scene::OnInput(SDL_Event) 
{
}

void Scene::Close() const
{
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
}

void Scene::RemoveActor(Actor* actor)
{
	
}

std::vector<Actor*> Scene::GetActors()
{
	return mActors;
}
