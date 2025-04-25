#pragma once
#include "BoxCollisionComponent.h"
#include "Core/Class/Actor/Actor.h"

class PolyCollisionComponent : public BoxCollisionComponent
{
private:
    Mesh* mMesh;
    Mesh LocalMesh;
public:
    PolyCollisionComponent(Actor* owner);
    PolyCollisionComponent(Actor* owner, Mesh* mesh);
    virtual ~PolyCollisionComponent();

    virtual void Draw(Matrix4Row viewProj);

    Mesh* GetMesh() const
    {
        return mMesh;
    }
};
