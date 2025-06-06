/**
 * @file Scene.cpp
 * @brief Implementation of the Scene class, representing a game scene.
 */

#include "Scene.h"

#include <algorithm>
#include "../../Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Miscellaneous/Actor/Camera.h"

Scene* Scene::ActiveScene = nullptr;

/**
 * @brief Loads resources required by the scene.
 */
void Scene::Load()
{
	Asset::LoadTexture(*mRenderer, "Resources/Textures/BaseTexture.png", "BaseTexture");
}

/**
 * @brief Unloads resources used by the scene and deletes all actors.
 */
void Scene::Unload()
{
	while(!mActors.empty())
	{
		delete mActors.back();
	}
	Asset::Clear();
}

/**
 * @brief Constructs a Scene object, initializes the camera, and sets this as the active scene.
 */
Scene::Scene(): mTitle(""), mRenderer(nullptr), mUpdatingActors(false)
{
	ActiveScene = this;
	mCamera = new Camera();
	AddActor(mCamera);
}

/**
 * @brief Destructor for Scene.
 */
Scene::~Scene()
{
	
}

/**
 * @brief Calls Start on all actors in the scene.
 */
void Scene::Start()
{
	for (Actor* actor : mActors)
	{
		actor->Start();
	}
}

/**
 * @brief Updates all actors in the scene.
 */
void Scene::Update()
{
	for (Actor* actor : mActors)
	{
		actor->Update();
	}
}

/**
 * @brief Renders the scene. (To be implemented)
 */
void Scene::Render()
{
}

/**
 * @brief Closes the scene, deletes all actors, and clears assets.
 */
void Scene::Close() const
{
	for (Actor* actor : mActors)
	{
		delete actor;
	}
	Asset::Clear();
}

/**
 * @brief Sets the renderer for the scene.
 * @param pRenderer Pointer to the renderer.
 */
void Scene::SetRenderer(IRenderer* pRenderer)
{
	mRenderer = pRenderer;
}

/**
 * @brief Sets the window for the scene.
 * @param pWindow Pointer to the window.
 */
void Scene::SetWindow(Window* pWindow)
{
	mCurrentWindow = pWindow;
}

/**
 * @brief Adds an actor to the scene.
 * @param actor Pointer to the actor to add.
 */
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

/**
 * @brief Removes an actor from the scene.
 * @param actor Pointer to the actor to remove.
 */
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

/**
 * @brief Updates all actors in the scene, including pending actors.
 */
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

/**
 * @brief Returns the list of actors in the scene.
 * @return Deque of pointers to actors.
 */
std::deque<Actor*> Scene::GetActors()
{
	return mActors;
}

/**
 * @brief Returns the renderer for the scene.
 * @return Reference to the renderer.
 */
IRenderer& Scene::GetRenderer()
{
	return *mRenderer;
}

/**
 * @brief Returns an actor of a specific class.
 * @param pClass Name of the class.
 * @param pValid Reference to a boolean set to true if found.
 * @param pIndex Index of the actor to retrieve.
 * @return Pointer to the actor.
 */
Actor* Scene::GetActorOfClass(std::string pClass, bool& pValid, int pIndex) const
{
	return GetActorsOfClass(pClass, pValid)[pIndex];
}

/**
 * @brief Returns all actors of a specific class.
 * @param pClass Name of the class.
 * @param pValid Reference to a boolean set to true if any found.
 * @return Vector of pointers to actors.
 */
std::vector<Actor*> Scene::GetActorsOfClass(std::string pClass, bool& pValid) const
{
	std::vector<Actor*> actors;
	for (Actor* actor : mActors)
	{
		if (actor->GetClass() == pClass)
			actors.push_back(actor);
	}
	pValid = !actors.empty();
	return actors;
}

/**
 * @brief Returns an actor by name.
 * @param pName Name of the actor.
 * @param pValid Reference to a boolean set to true if found.
 * @param pIndex Index of the actor to retrieve.
 * @return Pointer to the actor.
 */
Actor* Scene::GetActorByName(std::string pName, bool& pValid, int pIndex) const
{
	return GetActorsByName(pName, pValid)[pIndex];
}

/**
 * @brief Returns all actors by name.
 * @param pName Name of the actor.
 * @param pValid Reference to a boolean set to true if any found.
 * @return Vector of pointers to actors.
 */
std::vector<Actor*> Scene::GetActorsByName(std::string pName, bool& pValid) const
{
	std::vector<Actor*> actors;
	for (Actor* actor : mActors)
	{
		if (actor->GetName() == pName)
			actors.push_back(actor);
	}
	pValid = !actors.empty();
	return actors;
}
