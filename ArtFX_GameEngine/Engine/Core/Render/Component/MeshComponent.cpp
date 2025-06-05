#include "MeshComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Class/Scene/Scene.h"
#include "Core/Render/OpenGL/VertexArray.h"

MeshComponent::MeshComponent(Actor* pOwner) : Component(pOwner), mMesh(nullptr), mTextureIndex(0), mVisible(true)
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
    mMesh->GetShaderProgram().setInteger("uTessellationLevel", mTessellationLevel);
    mMesh->GetShaderProgram().setVector2f("uTiling", mTiling);
    Texture* texture = mMesh->GetTexture(mTextureIndex);
    
    if (texture)
    {
        texture->SetActive();
    }

    //Active NoiseTexture
    glActiveTexture(GL_TEXTURE1);
    if (mMesh->GetTexture(1) != nullptr)
    {
        mMesh->GetTexture(1)->SetActive();
    }
    
    mMesh->GetVertexArray()->SetActive();
    glPointSize(6.0f);
    glDrawArrays(mUseTessellation ? GL_PATCHES : GL_TRIANGLES, 0, mMesh->GetVerticesCount());

    //Active Albedo Texture
    glActiveTexture(GL_TEXTURE0);
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

void MeshComponent::SetVisible(bool pVisible)
{
    mVisible = pVisible;
}

