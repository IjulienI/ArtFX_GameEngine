#pragma once

#include "../../Scene.h"
#include "../../Engine/Component.h"
#include "../../Engine/Maths/Transform2D.h"

class BoxColliderComponent : public Component
{
protected:
    Vec2 mSize;
    Scene* mScene = nullptr;
    float mMaxDistance;

public:
    bool mCollision = false;
    
public:
    BoxColliderComponent(Actor& owner, Vec2 size, int updateOrder = 0, float maxDistance = 25.0f);
    BoxColliderComponent() = delete;
    
    void OnStart() override;
    void Update() override;
    void OnEnd() override;

    Vec2 GetSize();
    bool Collision(BoxColliderComponent* component, Vec2 actorLocation);
    
};
