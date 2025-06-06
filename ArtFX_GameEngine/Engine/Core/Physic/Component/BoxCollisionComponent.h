/**
 * @file BoxCollisionComponent.h
 * @brief Declaration of the BoxCollisionComponent class, representing a box-shaped collision component.
 */

#pragma once
#include "BaseCollisionComponent.h"
#include "Core/Class/Mesh/Mesh.h"

/**
 * @class BoxCollisionComponent
 * @brief Collision component for axis-aligned bounding boxes.
 */
class BoxCollisionComponent : public BaseCollisionComponent
{
protected:
    /**
     * @brief The bounding box for collision.
     */
    Box mBoundingBox;

    /**
     * @brief The radius of the bounding box.
     */
    float mRadius;

    /**
     * @brief Vertex array for rendering the box.
     */
    VertexArray* mVertexArray;

    /**
     * @brief Shader program for rendering.
     */
    ShaderProgram mShaderProgram;

    /**
     * @brief Vertex and fragment shaders.
     */
    Shader mVertexShader, mFragmentShader;
public:
    /**
     * @brief Constructs a BoxCollisionComponent using the owner's mesh bounding box.
     * @param owner Pointer to the owning Actor.
     */
    BoxCollisionComponent(Actor* owner);

    /**
     * @brief Constructs a BoxCollisionComponent with a specified bounding box.
     * @param owner Pointer to the owning Actor.
     * @param box The bounding box to use.
     */
    BoxCollisionComponent(Actor* owner, const Box box);

    /**
     * @brief Destructor.
     */
    virtual ~BoxCollisionComponent();

    /**
     * @brief Draws the box collision shape.
     * @param viewProj The view-projection matrix.
     */
    void Draw(Matrix4Row viewProj) override;

    /**
     * @brief Sets the bounding box for the collision component.
     * @param box The new bounding box.
     */
    void SetBoundingBox(const Box& box);

    /**
     * @brief Gets the bounding box.
     * @return The bounding box.
     */
    Box GetBoundingBox() const
    {
        return mBoundingBox;
    }

    /**
     * @brief Gets the radius of the bounding box.
     * @return The radius.
     */
    float GetRadius() const
    {
        return mRadius;
    }

    /**
     * @brief Generates the box geometry for rendering.
     */
    void GenerateBox();

    /**
     * @brief Gets the 8 vertices of the box in world space.
     * @return Vector of 8 Vec3 vertices.
     */
    std::vector<Vec3> GetVerticesInWorldSpace() const override;
};
