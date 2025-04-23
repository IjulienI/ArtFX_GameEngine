#pragma once
#include "BaseCollisionComponent.h"

class SphereCollisionComponent : public BaseCollisionComponent
{
private:
    float mRadius;
public:
    SphereCollisionComponent(Actor* actor);
    SphereCollisionComponent(Actor* actor, float radius);
    virtual ~SphereCollisionComponent();

    void SetRadius(float radius);
    float GetRadius() const
    {
        return mRadius;
    }
};
