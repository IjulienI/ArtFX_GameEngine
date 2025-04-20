#include "Mesh.h"

#include "Core/Render/Asset.h"
#include "Core/Render/OpenGL/VertexArray.h"

Mesh::Mesh() : mVertexArray(nullptr)
{
    mVertexArray = new VertexArray(cubeVertices, 28, cubeIndices, 36);
    mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
    mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    mTextures.emplace_back(&Asset::GetTexture("TUTUTUTU"));
}

Mesh::Mesh(std::vector<Vertex> vertices) : mVertices(std::move(vertices)), mVertexArray(nullptr)
{
}

void Mesh::Unload()
{
    delete mVertexArray;
    mVertexArray = nullptr;
}

void Mesh::AddTexture(Texture* pTexture)
{
    mTextures.emplace_back(pTexture);
}

void Mesh::SetShaderProgram(ShaderProgram*& pShaderProgram)
{
    mShaderProgram = *pShaderProgram;
}

void Mesh::SetVertexArray(VertexArray* pVertexArray)
{
    mVertexArray = pVertexArray;
}

int Mesh::GetVerticesCount() const
{
    return static_cast<int>(mVertices.size());
}

Texture* Mesh::GetTexture(size_t index)
{
    if (index > mTextures.size())
    {
        return nullptr;
    }
    return mTextures[index];
}
