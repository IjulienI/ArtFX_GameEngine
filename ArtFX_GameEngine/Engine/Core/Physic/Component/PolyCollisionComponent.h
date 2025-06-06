/**
 * @file PolyCollisionComponent.h
 * @brief Declaration of the PolyCollisionComponent class, representing a mesh-based collision component.
 */

#pragma once
#include "BoxCollisionComponent.h"
#include "Core/Class/Actor/Actor.h"

/**
 * @class PolyCollisionComponent
 * @brief Collision component for mesh-based collision shapes.
 */
class PolyCollisionComponent : public BoxCollisionComponent
{
private:
    /**
     * @brief Pointer to the mesh used for collision.
     */
    Mesh* mMesh;

    /**
     * @brief Local copy of the mesh for rendering.
     */
    Mesh LocalMesh;
public:
    /**
     * @brief Constructs a PolyCollisionComponent using the owner's mesh.
     * @param owner Pointer to the owning Actor.
     */
    PolyCollisionComponent(Actor* owner);

    /**
     * @brief Constructs a PolyCollisionComponent with a specified mesh.
     * @param owner Pointer to the owning Actor.
     * @param mesh Pointer to the mesh to use.
     */
    PolyCollisionComponent(Actor* owner, Mesh* mesh);

    /**
     * @brief Destructor.
     */
    virtual ~PolyCollisionComponent();

    /**
     * @brief Draws the mesh collision shape.
     * @param viewProj The view-projection matrix.
     */
    virtual void Draw(Matrix4Row viewProj);

    /**
     * @brief Gets the mesh used for collision.
     * @return Pointer to the mesh.
     */
    Mesh* GetMesh() const
    {
        return mMesh;
    }
};
