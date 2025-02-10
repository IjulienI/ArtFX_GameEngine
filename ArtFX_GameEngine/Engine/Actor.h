#pragma once
#include <vector>

#include "ActorState.h"
#include "../Scene.h"
#include "Maths/Transform2D.h"

class Component;

class Actor
{
private:
    Scene& mScene;
    ActorState mActorState;
    Transform2D mTransform;
    std::vector<Component> mComponents;

public:
    
    Actor() = delete;

public:
    void Initialize();
    void Start();
    void AttachScene(Scene& scene);
    void AddComponent(Component component);
    void RemoveComponent();
    void SetActive();
    void Update();
    void Destroy();
};
