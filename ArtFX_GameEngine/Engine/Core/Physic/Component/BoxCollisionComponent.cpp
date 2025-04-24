#include "BoxCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/OpenGL/VertexArray.h"

BoxCollisionComponent::BoxCollisionComponent(Actor* owner) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    mBoundingBox = owner->GetComponent<MeshComponent>()->GetMesh()->GetBoundingBox();
    GenerateBox();
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
}

BoxCollisionComponent::BoxCollisionComponent(Actor* owner, const Box box) : BaseCollisionComponent(owner)
{
    mCollisionType = CollisionType::Box;
    mBoundingBox = box;
    GenerateBox();
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
}

BoxCollisionComponent::~BoxCollisionComponent() = default;

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

void BoxCollisionComponent::SetBoundingBox(const Box& box)
{
    mBoundingBox = box;
}

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

std::vector<Vec3> BoxCollisionComponent::GetVerticesInWorldSpace() const
{
    std::vector<Vec3> worldVertices;

    Box localBox = mOwner->GetComponent<MeshComponent>()->GetMesh()->GetBoundingBox();

    Vec3 corners[8] = {
        { Vec3(localBox.min.x, localBox.min.y, localBox.min.z) },
        { Vec3(localBox.max.x, localBox.min.y, localBox.min.z) },
        { Vec3(localBox.max.x, localBox.max.y, localBox.min.z) },
        { Vec3(localBox.min.x, localBox.max.y, localBox.min.z) },
        { Vec3(localBox.min.x, localBox.min.y, localBox.max.z) },
        { Vec3(localBox.max.x, localBox.min.y, localBox.max.z) },
        { Vec3(localBox.max.x, localBox.max.y, localBox.max.z) },
        { Vec3(localBox.min.x, localBox.max.y, localBox.max.z) }
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

