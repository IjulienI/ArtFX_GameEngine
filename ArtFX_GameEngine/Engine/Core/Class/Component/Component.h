#pragma once
#include "Math/Matrix4Row.h"

class Actor;

class Component
{
protected:
    bool mActive = true;
    Actor* mOwner;
    int mUpdateOrder;
    Matrix4Row mWorldTransform;
    
public:
    Component(Actor* owner, int updateOrder = 0);
    Component() = delete;
    virtual ~Component();

    void SetTransform(Matrix4Row pWorldTransform);

    virtual void OnStart();
    virtual void Update();
    virtual void OnEnd();
};
