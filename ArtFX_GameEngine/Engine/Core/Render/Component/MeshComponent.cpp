#include "MeshComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Class/Scene/Scene.h"
#include "Core/Render/OpenGL/VertexArray.h"

MeshComponent::MeshComponent(Actor* pOwner) : Component(pOwner), mMesh(nullptr), mTextureIndex(0)
{
    glPatchParameteri(GL_PATCH_VERTICES, 3);
}

MeshComponent::~MeshComponent()
{
    Scene::ActiveScene->GetRenderer().RemoveMesh(this);
}

void MeshComponent::Draw(Matrix4Row viewProj)
{
    if (!mMesh) return;
    Matrix4Row wt = mOwner->GetWorldTransform();
    mMesh->GetShaderProgram().Use();
    mMesh->GetShaderProgram().setMatrix4Row("uViewProj", viewProj);
    mMesh->GetShaderProgram().setMatrix4Row("uWorldTransform", wt);
    Texture* texture = mMesh->GetTexture(mTextureIndex);
    if (texture)
    {
        texture->SetActive();
    }
    mMesh->GetVertexArray()->SetActive();
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetVerticesCount());
}

void MeshComponent::SetMesh(Mesh& mesh)
{
    mMesh = &mesh;
    Scene::ActiveScene->GetRenderer().AddMesh(this);
}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
    mTextureIndex = pTextureIndex;
}

void MeshComponent::AddTexture(Texture& pTexture)
{
    mMesh->AddTexture(&pTexture);
}
