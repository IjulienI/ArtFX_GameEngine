#pragma once
#include <vector>

#include "ActorState.h"
#include "../Scene/Scene.h"
#include "../../../Math/Transform2D.h"
#include "../Component/Component.h"

class Actor
{
protected:
    Scene& mScene;
    ActorState mActorState;
    Transform2D mTransform;
    
private:
    std::vector<Component*> mComponents;

public:
    Actor(Transform2D location, ActorState state);
    Actor() = delete;
    virtual ~Actor() = default;

protected:
    virtual void Initialize();
    
public:
    virtual void Start();
    virtual void Update();
    virtual void Destroy();
    
public:
    void AttachScene(const Scene& scene);
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void SetActive(ActorState state);

public:
    Vec2 GetLocation();
    Vec2 GetRotation();
    Vec2 GetScale();
    Transform2D GetTransform();
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
};

