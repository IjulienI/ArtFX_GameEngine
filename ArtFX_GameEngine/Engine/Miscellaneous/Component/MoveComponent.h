#pragma once
#include "Core/Class/Component/Component.h"
#include "Math/Vec2.h"

class MoveComponent : public Component
{
protected:
    Vec2 mSpeed;
    
public:
    MoveComponent(Actor* owner, int updateOrder = 100);
    MoveComponent() = delete;
    MoveComponent(const MoveComponent&) = delete;
    MoveComponent& operator= (const MoveComponent&) = delete;

    Vec2 GetSpeed() const;
    void SetSpeed(Vec2 speed);

    void Update() override;

    
};
