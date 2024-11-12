#include "Scene.h"

Scene::Scene(Renderer* pRenderer, std::string pTitle): mRenderer(pRenderer), mTitle(pTitle)
{
}

void Scene::Start()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
	Rectangle rect = { 150, 150, 50, 150 };

	mRenderer->DrawRect(rect);
}

void Scene::OnInput(SDL_Event)
{
}

void Scene::Close()
{
}
