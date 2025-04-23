#pragma once
#include "BoxCollisionComponent.h"
#include "Core/Class/Actor/Actor.h"

class PolyCollisionComponent : public BoxCollisionComponent
{
private:
    Mesh* mMesh;
public:
    PolyCollisionComponent(Actor* owner);
    virtual ~PolyCollisionComponent();

    Mesh* GetMesh();
};
