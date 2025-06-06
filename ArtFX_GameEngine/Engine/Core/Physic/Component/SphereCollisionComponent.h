/**
 * @file SphereCollisionComponent.h
 * @brief Declaration of the SphereCollisionComponent class, representing a sphere-shaped collision component.
 */

#pragma once
#include "BaseCollisionComponent.h"
#include "Core/Render/Shader/ShaderProgram.h"

class VertexArray;

/**
 * @class SphereCollisionComponent
 * @brief Collision component for spherical collision shapes.
 */
class SphereCollisionComponent : public BaseCollisionComponent
{
private:
    /**
     * @brief The radius of the sphere.
     */
    float mRadius;

    /**
     * @brief The center of the sphere.
     */
    Vec3 mCenter;

    /**
     * @brief Vertex array for rendering the sphere.
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
     * @brief Constructs a SphereCollisionComponent using the owner's mesh radius.
     * @param actor Pointer to the owning Actor.
     */
    SphereCollisionComponent(Actor* actor);

    /**
     * @brief Constructs a SphereCollisionComponent with a specified radius.
     * @param actor Pointer to the owning Actor.
     * @param radius The sphere radius.
     */
    SphereCollisionComponent(Actor* actor, float radius);

    /**
     * @brief Destructor.
     */
    ~SphereCollisionComponent() override;

    /**
     * @brief Draws the sphere collision shape.
     * @param viewProj The view-projection matrix.
     */
    void Draw(Matrix4Row viewProj) override;

    /**
     * @brief Generates the sphere geometry for rendering.
     * @param radius The radius of the sphere.
     */
    void GenerateSphere(float radius);

    /**
     * @brief Sets the radius of the sphere and regenerates geometry.
     * @param radius The new radius.
     */
    void SetRadius(float radius);

    /**
     * @brief Gets the radius of the sphere.
     * @return The radius.
     */
    float GetRadius() const
    {
        return mRadius;
    }

    /**
     * @brief Gets the vertices of the sphere in world space.
     * @return Vector of Vec3 vertices.
     */
    std::vector<Vec3> GetVerticesInWorldSpace() const override;
};
