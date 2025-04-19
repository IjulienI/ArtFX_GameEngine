#pragma once

#include <vector>
#include "ActorState.h"
#include "../Scene/Scene.h"
#include "../Component/Component.h"

class Transform;

class Actor
{
protected:
    Scene* mScene;
    ActorState mActorState;
    Transform mTransform;
    
private:
    std::vector<Component*> mComponents;

public:
    Actor(Transform location, ActorState state);
    Actor();
    virtual ~Actor() = default;

protected:
    virtual void Initialize();
    
public:
    virtual void Start();
    virtual void Update();
    virtual void Destroy();
    
public:
    void AttachScene(Scene& scene);
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void SetActive(ActorState state);
    void UpdateComponentsTransform();

public:
    Vec3 GetLocation();
    Quaternion GetRotation();
    Vec3 GetScale();
    Transform GetTransform();
    Scene* GetScene();
    std::vector<Component*> GetComponents();
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

    void SetLocation(Vec3 loc);
    void SetScale(Vec3 scale);
};

