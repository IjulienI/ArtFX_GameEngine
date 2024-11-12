#include "Scene.h"
#include <iostream>

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
