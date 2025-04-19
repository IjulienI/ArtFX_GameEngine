#pragma once

#include "Math/Transform.h"

class Actor;

class Component
{
protected:
    bool mActive = true;
    Actor* mOwner;
    int mUpdateOrder;
    Transform mWorldTransform;
    
public:
    Component(Actor* owner, int updateOrder = 0);
    Component() = delete;
    virtual ~Component();

    void SetTransform(Transform pWorldTransform);

    virtual void OnStart();
    virtual void Update();
    virtual void OnEnd();
};
