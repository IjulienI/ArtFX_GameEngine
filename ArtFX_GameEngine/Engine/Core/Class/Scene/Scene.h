/**
 * @file Scene.h
 * @brief Declaration of the Scene class, representing a game scene containing actors and rendering logic.
 */

#pragma once
#include "../../Render/RendererSdl.h"
#include <string>
#include <deque>

class Camera;
class Actor;

/**
 * @class Scene
 * @brief Represents a game scene containing actors, a camera, and rendering logic.
 */
class Scene
{
public:
	/**
	 * @brief Pointer to the currently active scene.
	 */
	static Scene* ActiveScene;
	
	/**
	 * @brief Renderer used for drawing the scene.
	 */
	IRenderer* mRenderer = nullptr;	
	
	/**
	 * @brief Pointer to the current window.
	 */
	Window* mCurrentWindow = nullptr;
	
protected: 
	/**
	 * @brief Title of the scene.
	 */
	std::string mTitle;

	/**
	 * @brief List of actors currently in the scene.
	 */
	std::deque<Actor*> mActors;

	/**
	 * @brief Actors pending to be added to the scene.
	 */
	std::deque<Actor*> mPendingActors;

	/**
	 * @brief Camera used in the scene.
	 */
	Camera* mCamera;

private:
	/**
	 * @brief Indicates if the actors are currently being updated.
	 */
	bool mUpdatingActors;
	
public:
	/**
	 * @brief Constructs a Scene object.
	 */
	Scene();

	/**
	 * @brief Destructor for Scene.
	 */
	virtual ~Scene();

	/**
	 * @brief Called when the scene starts.
	 */
	virtual void Start();

	/**
	 * @brief Updates the scene and its actors.
	 */
	virtual void Update();

	/**
	 * @brief Renders the scene.
	 */
	virtual void Render();

	/**
	 * @brief Closes the scene and releases resources.
	 */
	virtual void Close() const;
	
	/**
	 * @brief Loads resources required by the scene.
	 */
	virtual void Load();

	/**
	 * @brief Unloads resources used by the scene.
	 */
	virtual void Unload();

	/**
	 * @brief Sets the renderer for the scene.
	 * @param pRenderer Pointer to the renderer.
	 */
	void SetRenderer(IRenderer* pRenderer);

	/**
	 * @brief Sets the window for the scene.
	 * @param pWindow Pointer to the window.
	 */
	void SetWindow(Window* pWindow);

public:
	/**
	 * @brief Adds an actor to the scene.
	 * @param actor Pointer to the actor to add.
	 */
	void AddActor(Actor* actor);

	/**
	 * @brief Removes an actor from the scene.
	 * @param actor Pointer to the actor to remove.
	 */
	void RemoveActor(Actor* actor);

	/**
	 * @brief Updates all actors in the scene.
	 */
	void UpdateActors();

public:
	/**
	 * @brief Gets the list of actors in the scene.
	 * @return Deque of pointers to actors.
	 */
	std::deque<Actor*> GetActors();

	/**
	 * @brief Gets the renderer for the scene.
	 * @return Reference to the renderer.
	 */
	IRenderer& GetRenderer();
	
	/**
	 * @brief Gets an actor of a specific class.
	 * @param pClass Name of the class.
	 * @param pValid Reference to a boolean set to true if found.
	 * @param pIndex Index of the actor to retrieve.
	 * @return Pointer to the actor.
	 */
	Actor* GetActorOfClass(std::string pClass, bool& pValid, int pIndex = 0) const;

	/**
	 * @brief Gets all actors of a specific class.
	 * @param pClass Name of the class.
	 * @param pValid Reference to a boolean set to true if any found.
	 * @return Vector of pointers to actors.
	 */
	std::vector<Actor*> GetActorsOfClass(std::string pClass, bool& pValid) const;

	/**
	 * @brief Gets an actor by name.
	 * @param pName Name of the actor.
	 * @param pValid Reference to a boolean set to true if found.
	 * @param pIndex Index of the actor to retrieve.
	 * @return Pointer to the actor.
	 */
	Actor* GetActorByName(std::string pName, bool& pValid, int pIndex = 0) const;

	/**
	 * @brief Gets all actors by name.
	 * @param pName Name of the actor.
	 * @param pValid Reference to a boolean set to true if any found.
	 * @return Vector of pointers to actors.
	 */
	std::vector<Actor*> GetActorsByName(std::string pName, bool& pValid) const;
};
