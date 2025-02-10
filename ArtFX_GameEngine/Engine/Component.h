#pragma once
#include "Actor.h"

class Component
{

protected:
    bool mActive;
    Actor& mOwner;
    int mUpdateOrder;
public:
    Component(Actor& owner, int updateOrder = 0 );
    Component() = delete;
    virtual ~Component();

    virtual void OnStart();
    virtual void Update();
    virtual void OnEnd();
};
