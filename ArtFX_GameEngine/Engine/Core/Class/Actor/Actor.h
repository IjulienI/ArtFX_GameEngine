#pragma once

#include <vector>
#include "ActorState.h"
#include "../Scene/Scene.h"
#include "../Component/Component.h"
#include "Math/Transform.h"

class  Actor
{
protected:
    Scene* mScene;
    ActorState mActorState;
    Transform mTransform;

    std::string mClassName;
    std::string mName;
    
private:
    std::vector<Component*> mComponents;

public:
    Actor();
    virtual ~Actor() = default;

protected:
    virtual void Initialize();
    
public:
    virtual void Start();
    virtual void Update();
    virtual void UpdateActor();
    virtual void Destroy();
    
public:
    void AttachScene(Scene& scene);
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void SetActive(ActorState state);
    void UpdateComponentsTransform();

public:

    std::string GetClass()
    {
        return mClassName;
    }
    std::string GetName()
    {
        return mName;
    }
    void SetName(std::string name);
    
    Vec3 GetLocation();
    Quaternion GetRotation();
    Vec3 GetScale();
    Transform& GetTransform();
    Matrix4Row GetWorldTransform();
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
    void AddLocation(Vec3 loc);
    void SetScale(Vec3 scale);
    void SetRotation(Quaternion rotation);

    void Rotate(Vec3 rotation);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
};

