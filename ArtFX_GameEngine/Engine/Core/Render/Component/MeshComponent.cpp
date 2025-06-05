#include "MeshComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Class/Scene/Scene.h"
#include "Core/Render/OpenGL/VertexArray.h"
#include "Math/Time.h"

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

    mTime += Time::deltaTime;
    
    Matrix4Row wt = mOwner->GetWorldTransform();
    mMesh->GetShaderProgram().Use();
    mMesh->GetShaderProgram().setMatrix4Row("uViewProj", viewProj);
    mMesh->GetShaderProgram().setMatrix4Row("uWorldTransform", wt);
    mMesh->GetShaderProgram().setInteger("uTessellationLevel", mTessellationLevel);
    mMesh->GetShaderProgram().setVector2f("uTiling", mTiling);
    mMesh->GetShaderProgram().setFloat("uDisplacementScale", mDisplacementScale);
    mMesh->GetShaderProgram().setFloat("uTime", mTime);

    //Active AlbedoTexture
    glActiveTexture(GL_TEXTURE0);
    Texture* albedoTexture = mMesh->GetTexture(mTextureIndex);
    if (albedoTexture)
    {
        albedoTexture->SetActive();
    }

    //Active NoiseTexture
    glActiveTexture(GL_TEXTURE1);
    Texture* noiseTexture = mMesh->GetNoiseTexture();
    if (noiseTexture)
    {
        noiseTexture->SetActive();
    }
    
    mMesh->GetVertexArray()->SetActive();
    glDrawArrays(mUseTessellation ? GL_PATCHES : GL_TRIANGLES, 0, mMesh->GetVerticesCount());
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

