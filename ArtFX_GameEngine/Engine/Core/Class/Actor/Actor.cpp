/**
 * @file Actor.cpp
 * @brief Implementation of the Actor class, representing a game object in the scene.
 */

#include "Actor.h"

#include <algorithm>
#include "../../../Debug/Log.h"
#include "Core/Class/Scene/Scene.h"
#include "Math/Transform.h"

/**
 * @brief Constructs an Actor, initializes and starts it.
 */
Actor::Actor() : mScene(Scene::ActiveScene), mActorState(ActorState::Active), mTransform(Transform(this))
{
    Actor::Initialize();
    Actor::Start();
}

/**
 * @brief Initializes the actor. Called upon creation.
 */
void Actor::Initialize()
{    
    Log::Info(mName + " of class " + mClassName + " initialized");
}

/**
 * @brief Starts the actor. Called after initialization.
 */
void Actor::Start()
{    
    Rotate(Vec3(45.0f, 0.0f, 0.0f));
}

/**
 * @brief Attaches the actor to a scene.
 * @param scene Reference to the scene.
 */
void Actor::AttachScene(Scene& scene)
{
    mScene = &scene;
}

/**
 * @brief Adds a component to the actor.
 * @param component Pointer to the component to add.
 */
void Actor::AddComponent(Component* component)
{
    mComponents.push_back(component);
}

/**
 * @brief Removes a component from the actor.
 * @param component Pointer to the component to remove.
 */
void Actor::RemoveComponent(Component* component)
{
    auto it = std::find(mComponents.begin(), mComponents.end(), component);
    if(it != mComponents.end())
    {
        iter_swap(it, mComponents.end() - 1);
        mComponents.pop_back();
    }
}

/**
 * @brief Sets the active state of the actor.
 * @param state New state of the actor.
 */
void Actor::SetActive(ActorState state)
{
    mActorState = state;
}

/**
 * @brief Updates the transform of all components attached to the actor.
 */
void Actor::UpdateComponentsTransform()
{
    for(Component* component : mComponents)
    {
        component->OnUpdateWorldTransform();
    }
}

/**
 * @brief Updates all components and the actor itself.
 */
void Actor::Update()
{
    for(Component* component : mComponents)
    {
        component->Update();
    }
    UpdateActor();
    mTransform.ComputeWorldTransform();
}

/**
 * @brief Updates the actor's specific logic. Can be overridden by subclasses.
 */
void Actor::UpdateActor()
{
}

/**
 * @brief Destroys the actor and removes it from the scene.
 */
void Actor::Destroy()
{
    mScene->RemoveActor(this);
}

/**
 * @brief Sets the name of the actor.
 * @param name New name.
 */
void Actor::SetName(std::string name)
{
    mName = name;
}

/**
 * @brief Gets the position of the actor.
 * @return Position as Vec3.
 */
Vec3 Actor::GetLocation()
{
    return mTransform.position;
}

/**
 * @brief Gets the rotation of the actor.
 * @return Rotation as Quaternion.
 */
Quaternion Actor::GetRotation()
{
    return mTransform.rotation;
}

/**
 * @brief Gets the scale of the actor.
 * @return Scale as Vec3.
 */
Vec3 Actor::GetScale()
{
    return mTransform.scale;
}

/**
 * @brief Gets the transform of the actor.
 * @return Reference to the Transform.
 */
Transform& Actor::GetTransform()
{
    return mTransform;
}

/**
 * @brief Gets the world transformation matrix of the actor.
 * @return 4x4 transformation matrix.
 */
Matrix4Row Actor::GetWorldTransform()
{
    return mTransform.GetWorldTransform();
}

/**
 * @brief Gets the scene the actor belongs to.
 * @return Pointer to the scene.
 */
Scene* Actor::GetScene()
{
    return mScene;
}

/**
 * @brief Gets the list of components attached to the actor.
 * @return Vector of component pointers.
 */
std::vector<Component*> Actor::GetComponents()
{
    return mComponents;
}

/**
 * @brief Sets the position of the actor.
 * @param loc New position.
 */
void Actor::SetLocation(Vec3 loc)
{
    mTransform.position = loc;
    mTransform.SetNeedsUpdate(true);
}

/**
 * @brief Adds an offset to the actor's position.
 * @param loc Offset to add.
 */
void Actor::AddLocation(Vec3 loc)
{
    mTransform.position += loc;
    mTransform.SetNeedsUpdate(true);
}

/**
 * @brief Sets the scale of the actor.
 * @param scale New scale.
 */
void Actor::SetScale(Vec3 scale)
{
    mTransform.scale = scale;
    mTransform.SetNeedsUpdate(true);
}

/**
 * @brief Sets the rotation of the actor.
 * @param rotation New rotation.
 */
void Actor::SetRotation(Quaternion rotation)
{
    mTransform.rotation = rotation;
    mTransform.SetNeedsUpdate(true);
}

/**
 * @brief Applies a rotation to the actor.
 * @param rotation Rotation to apply (in degrees).
 */
void Actor::Rotate(Vec3 rotation)
{
    mTransform.Rotate(rotation);
}

/**
 * @brief Applies a rotation around the X axis.
 * @param rotation Angle in degrees.
 */
void Actor::RotateX(float rotation)
{
    mTransform.RotateX(rotation);
}

/**
 * @brief Applies a rotation around the Y axis.
 * @param rotation Angle in degrees.
 */
void Actor::RotateY(float rotation)
{
    mTransform.RotateY(rotation);
}

/**
 * @brief Applies a rotation around the Z axis.
 * @param rotation Angle in degrees.
 */
void Actor::RotateZ(float rotation)
{
    mTransform.RotateZ(rotation);
}
