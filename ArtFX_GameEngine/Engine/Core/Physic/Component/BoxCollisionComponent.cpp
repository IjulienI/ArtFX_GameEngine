/**
 * @file BoxCollisionComponent.cpp
 * @brief Implementation of the BoxCollisionComponent class, representing a box-shaped collision component.
 */

#include "BoxCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/OpenGL/VertexArray.h"

/**
 * @brief Constructs a BoxCollisionComponent using the owner's mesh bounding box.
 * @param owner Pointer to the owning Actor.
 */
BoxCollisionComponent::BoxCollisionComponent(Actor* owner) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    MeshComponent* mesh = owner->GetComponent<MeshComponent>();
    mBoundingBox = mesh->GetMesh()->GetBoundingBox();
    mRadius = mesh->GetMesh()->GetRadius();
    GenerateBox();
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    mShaderProgram.setVector3f("randomColor",
        Vec3(0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX))
    );
}

/**
 * @brief Constructs a BoxCollisionComponent with a specified bounding box.
 * @param owner Pointer to the owning Actor.
 * @param box The bounding box to use.
 */
BoxCollisionComponent::BoxCollisionComponent(Actor* owner, const Box box) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    mBoundingBox = box;                                                              
    GenerateBox();
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    mShaderProgram.setVector3f("randomColor",
        Vec3(0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX))
    );
}

/**
 * @brief Destructor for BoxCollisionComponent.
 */
BoxCollisionComponent::~BoxCollisionComponent() = default;

/**
 * @brief Draws the box collision shape.
 * @param viewProj The view-projection matrix.
 */
void BoxCollisionComponent::Draw(Matrix4Row viewProj)
{
    BaseCollisionComponent::Draw(viewProj);

    Matrix4Row wt = mOwner->GetWorldTransform();
    
    mShaderProgram.Use();
    mShaderProgram.setMatrix4Row("uViewProj", viewProj);
    mShaderProgram.setMatrix4Row("uWorldTransform", wt);

    mVertexArray->SetActive();
    glDrawArrays(GL_TRIANGLES, 0, mVertexArray->GetVerticeCount());
}

/**
 * @brief Sets the bounding box for the collision component.
 * @param box The new bounding box.
 */
void BoxCollisionComponent::SetBoundingBox(const Box& box)
{
    mBoundingBox = box;
    GenerateBox();
}

/**
 * @brief Generates the box geometry for rendering.
 */
void BoxCollisionComponent::GenerateBox()
{
    std::vector<float> vertices;

    Vec3 min = mBoundingBox.min;
    Vec3 max = mBoundingBox.max;

    Vec3 corners[8] = {
        Vec3(min.x, min.y, min.z),
        Vec3(max.x, min.y, min.z),
        Vec3(max.x, max.y, min.z),
        Vec3(min.x, max.y, min.z),
        Vec3(min.x, min.y, max.z),
        Vec3(max.x, min.y, max.z),
        Vec3(max.x, max.y, max.z),
        Vec3(min.x, max.y, max.z) 
    };

    int faces[36] = {
        0, 1, 2, 0, 2, 3,
        5, 4, 7, 5, 7, 6,
        4, 0, 3, 4, 3, 7,
        1, 5, 6, 1, 6, 2,
        3, 2, 6, 3, 6, 7,
        4, 5, 1, 4, 1, 0
    };

    for (int i = 0; i < 36; ++i)
    {
        Vec3 pos = corners[faces[i]];
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
    }

    mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned int>(vertices.size() / 8));
}

/**
 * @brief Gets the 8 vertices of the box in world space.
 * @return Vector of 8 Vec3 vertices.
 */
std::vector<Vec3> BoxCollisionComponent::GetVerticesInWorldSpace() const
{
    std::vector<Vec3> worldVertices;

    Vec3 corners[8] = {
        { Vec3(mBoundingBox.min.x, mBoundingBox.min.y, mBoundingBox.min.z) },
        { Vec3(mBoundingBox.max.x, mBoundingBox.min.y, mBoundingBox.min.z) },
        { Vec3(mBoundingBox.max.x, mBoundingBox.max.y, mBoundingBox.min.z) },
        { Vec3(mBoundingBox.min.x, mBoundingBox.max.y, mBoundingBox.min.z) },
        { Vec3(mBoundingBox.min.x, mBoundingBox.min.y, mBoundingBox.max.z) },
        { Vec3(mBoundingBox.max.x, mBoundingBox.min.y, mBoundingBox.max.z) },
        { Vec3(mBoundingBox.max.x, mBoundingBox.max.y, mBoundingBox.max.z) },
        { Vec3(mBoundingBox.min.x, mBoundingBox.max.y, mBoundingBox.max.z) }
    };

    Quaternion rotation = mOwner->GetRotation();
    Vec3 position = mOwner->GetLocation();
    Vec3 scale = mOwner->GetScale();

    for (Vec3 corner : corners)
    {
        Vec3 scaledCorner = corner * scale;
        Vec3 worldCorner = rotation * scaledCorner + position;
        worldVertices.push_back(worldCorner);
    }

    return worldVertices;
}
