#include "PolyCollisionComponent.h"

#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/OpenGL/VertexArray.h"

PolyCollisionComponent::PolyCollisionComponent(Actor* owner) : BoxCollisionComponent(owner)
{
    mCollisionType = CollisionType::Mesh;
    mMesh = mOwner->GetComponent<MeshComponent>()->GetMesh();
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    mShaderProgram.setVector3f("randomColor",
        Vec3(0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
             0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX))
    );
}

PolyCollisionComponent::PolyCollisionComponent(Actor* owner, Mesh* mesh) : BoxCollisionComponent(owner), mMesh(mesh)
{
    mCollisionType = CollisionType::Mesh;
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    mShaderProgram.setVector3f("randomColor",
    Vec3(0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
         0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX),
         0.5f + static_cast<float>(rand()) / (2.0f * RAND_MAX))
);
}

PolyCollisionComponent::~PolyCollisionComponent() = default;

void PolyCollisionComponent::Draw(Matrix4Row viewProj)
{
    if (!mMesh) return;
    LocalMesh = *mMesh;
    Matrix4Row wt = mOwner->GetWorldTransform();
    mShaderProgram.Use();
    mShaderProgram.setMatrix4Row("uViewProj", viewProj);
    mShaderProgram.setMatrix4Row("uWorldTransform", wt);
    LocalMesh.GetVertexArray()->SetActive();
    glDrawArrays(GL_TRIANGLES, 0, LocalMesh.GetVerticesCount());    
}
