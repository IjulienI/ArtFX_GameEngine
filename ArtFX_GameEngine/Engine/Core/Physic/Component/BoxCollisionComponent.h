#pragma once
#include "BaseCollisionComponent.h"
#include "Core/Class/Mesh/Mesh.h"

class BoxCollisionComponent : public BaseCollisionComponent
{
private:
    Box mBoundingBox;
public:
    BoxCollisionComponent(Actor* owner);
    BoxCollisionComponent(Actor* owner, const Box box);
    virtual ~BoxCollisionComponent();

    void SetBoundingBox(const Box& box);
    Box GetBoundingBox() const
    {
        return mBoundingBox;
    }
};
