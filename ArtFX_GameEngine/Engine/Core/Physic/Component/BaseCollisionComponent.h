/**
 * @file BaseCollisionComponent.h
 * @brief Declaration of the BaseCollisionComponent class, the base class for all collision components.
 */

#pragma once
#include <vector>
#include "Core/Class/Component/Component.h"

/**
 * @enum CollisionType
 * @brief Types of collision shapes supported.
 */
enum class CollisionType
{
    Box,    /**< Axis-aligned bounding box collision. */
    Sphere, /**< Spherical collision. */
    Mesh    /**< Mesh-based collision. */
};

/**
 * @class BaseCollisionComponent
 * @brief Abstract base class for all collision components.
 */
class BaseCollisionComponent : public Component
{
protected:
    /**
     * @brief The type of collision shape.
     */
    CollisionType mCollisionType;
public:
    /**
     * @brief Constructs a BaseCollisionComponent.
     * @param pOwner Pointer to the owning Actor.
     */
    BaseCollisionComponent(Actor* pOwner);

    /**
     * @brief Virtual destructor.
     */
    virtual ~BaseCollisionComponent();

    /**
     * @brief Draws the collision shape.
     * @param viewProj The view-projection matrix.
     */
    virtual void Draw(Matrix4Row viewProj);

    /**
     * @brief Gets the type of collision shape.
     * @return The collision type.
     */
    CollisionType GetCollisionType() const
    {
        return mCollisionType;
    }

    /**
     * @brief Gets the vertices of the collision shape in world space.
     * @return Vector of vertices in world space.
     */
    virtual std::vector<Vec3> GetVerticesInWorldSpace() const = 0;
};
