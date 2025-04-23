#pragma once
#include <vector>

#include "Core/Class/Component/Component.h"

enum class CollisionType
{
    Box,
    Sphere,
    Mesh
};

class BaseCollisionComponent : public Component
{
protected:
    CollisionType mCollisionType;
public:
    BaseCollisionComponent(Actor* pOwner);
    virtual ~BaseCollisionComponent();

    CollisionType GetCollisionType() const
    {
        return mCollisionType;
    }

    std::vector<Vec3> GetVerticesInWorldSpace() const;
};
