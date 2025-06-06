#pragma once

#include <vector>
#include "ActorState.h"
#include "../Scene/Scene.h"
#include "../Component/Component.h"
#include "Math/Transform.h"

/**
 * @brief Base class representing an actor in the scene.
 * 
 * An actor is a game object that can contain components and be manipulated in the scene.
 */
class Actor
{
protected:
    /**
     * @brief Pointer to the scene this actor belongs to.
     */
    Scene* mScene;

    /**
     * @brief Current state of the actor (active, inactive, etc.).
     */
    ActorState mActorState;

    /**
     * @brief Spatial transformations of the actor (position, rotation, scale).
     */
    Transform mTransform;

    /**
     * @brief Name of the actor's class.
     */
    std::string mClassName;

    /**
     * @brief Name of the actor.
     */
    std::string mName;
    
private:
    /**
     * @brief List of components attached to this actor.
     */
    std::vector<Component*> mComponents;

public:
    /**
     * @brief Actor constructor.
     */
    Actor();

    /**
     * @brief Virtual destructor.
     */
    virtual ~Actor() = default;

protected:
    /**
     * @brief Initializes the actor (called upon creation).
     */
    virtual void Initialize();
    
public:
    /**
     * @brief Starts the actor (called after initialization).
     */
    virtual void Start();

    /**
     * @brief Updates the actor and its components.
     */
    virtual void Update();

    /**
     * @brief Updates the actor's specific logic.
     */
    virtual void UpdateActor();

    /**
     * @brief Destroys the actor and removes it from the scene.
     */
    virtual void Destroy();
    
public:
    /**
     * @brief Attaches the actor to a scene.
     * @param scene Reference to the scene.
     */
    void AttachScene(Scene& scene);

    /**
     * @brief Adds a component to the actor.
     * @param component Pointer to the component to add.
     */
    void AddComponent(Component* component);

    /**
     * @brief Removes a component from the actor.
     * @param component Pointer to the component to remove.
     */
    void RemoveComponent(Component* component);

    /**
     * @brief Sets the active state of the actor.
     * @param state New state of the actor.
     */
    void SetActive(ActorState state);

    /**
     * @brief Updates the transform of all components.
     */
    void UpdateComponentsTransform();

public:
    /**
     * @brief Returns the class name of the actor.
     * @return Class name.
     */
    std::string GetClass()
    {
        return mClassName;
    }

    /**
     * @brief Returns the name of the actor.
     * @return Actor name.
     */
    std::string GetName()
    {
        return mName;
    }

    /**
     * @brief Sets the name of the actor.
     * @param name New name.
     */
    void SetName(std::string name);
    
    /**
     * @brief Returns the position of the actor.
     * @return Position (Vec3).
     */
    Vec3 GetLocation();

    /**
     * @brief Returns the rotation of the actor.
     * @return Rotation (Quaternion).
     */
    Quaternion GetRotation();

    /**
     * @brief Returns the scale of the actor.
     * @return Scale (Vec3).
     */
    Vec3 GetScale();

    /**
     * @brief Returns the transform of the actor.
     * @return Reference to the Transform.
     */
    Transform& GetTransform();

    /**
     * @brief Returns the global transformation matrix.
     * @return 4x4 matrix (Matrix4Row).
     */
    Matrix4Row GetWorldTransform();

    /**
     * @brief Returns the scene the actor belongs to.
     * @return Pointer to the scene.
     */
    Scene* GetScene();

    /**
     * @brief Returns the list of components attached to the actor.
     * @return Vector of component pointers.
     */
    std::vector<Component*> GetComponents();

    /**
     * @brief Returns the first component of the specified type attached to the actor.
     * @tparam T Type of the component to search for.
     * @return Pointer to the component or nullptr if not found.
     */
    template<typename T>T* GetComponent()
    {
        for(auto component : mComponents)
        {
            T* result = dynamic_cast<T*>(component);
            if(result)
            {
                return result;
            }
        }
        return nullptr;
    }

    /**
     * @brief Sets the position of the actor.
     * @param loc New position.
     */
    void SetLocation(Vec3 loc);

    /**
     * @brief Adds an offset to the actor's position.
     * @param loc Offset to add.
     */
    void AddLocation(Vec3 loc);

    /**
     * @brief Sets the scale of the actor.
     * @param scale New scale.
     */
    void SetScale(Vec3 scale);

    /**
     * @brief Sets the rotation of the actor.
     * @param rotation New rotation.
     */
    void SetRotation(Quaternion rotation);

    /**
     * @brief Applies a rotation to the actor.
     * @param rotation Rotation to apply (in degrees).
     */
    void Rotate(Vec3 rotation);

    /**
     * @brief Applies a rotation around the X axis.
     * @param angle Angle in degrees.
     */
    void RotateX(float angle);

    /**
     * @brief Applies a rotation around the Y axis.
     * @param angle Angle in degrees.
     */
    void RotateY(float angle);

    /**
     * @brief Applies a rotation around the Z axis.
     * @param angle Angle in degrees.
     */
    void RotateZ(float angle);
};

