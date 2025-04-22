#pragma once
#include "Core/Class/Component/Component.h"

class RigidbodyComponent : public Component
{
private:
    bool mIsStatic;
    bool mIsColliding;
public:
    RigidbodyComponent(Actor* pOwner);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;

    void SetStatic(bool pStatic);
    void SetColliding(bool pColliding);
};
