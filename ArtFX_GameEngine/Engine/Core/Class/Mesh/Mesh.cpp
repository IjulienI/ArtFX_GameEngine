#include "Mesh.h"

#include "Core/Render/Asset.h"
#include "Core/Render/OpenGL/VertexArray.h"

Mesh::Mesh() : mVertexArray(nullptr)
{
    mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
    mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    AddTexture(&Asset::GetTexture("BaseTexture"));
}

Mesh::Mesh(std::vector<Vertex> vertices) : mVertices(std::move(vertices)), mVertexArray(nullptr)
{
    float* verticeInfo = ToVerticeArray();
    mVertexArray = new VertexArray(verticeInfo, mVertices.size());
    delete[] verticeInfo;
    verticeInfo = nullptr;
    mVertexShader.Load("BasicMesh.vert", ShaderType::VERTEX);
    mFragmentShader.Load("BasicMesh.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
    AddTexture(&Asset::GetTexture("BaseTexture"));
}

void Mesh::Unload()
{
    delete mVertexArray;
    mVertexArray = nullptr;
}

void Mesh::AddTexture(Texture* pTexture)
{
    if (!mTextures.empty())
    {        
        if (mTextures[0] == &Asset::GetTexture("BaseTexture"))
        {
            mTextures.clear();
        }
    }
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

void Mesh::SetRadius(float radius)
{
    mRadius = radius;
}

float* Mesh::ToVerticeArray()
{
    float* array = new float[mVertices.size() * 8];
    int counter = 0;
    for (int i = 0; i < mVertices.size(); i++)
    {
        array[counter] = mVertices[i].position.x;
        array[counter + 1] = mVertices[i].position.y;
        array[counter + 2] = mVertices[i].position.z;
        array[counter + 3] = mVertices[i].normal.x;
        array[counter + 4] = mVertices[i].normal.y;
        array[counter + 5] = mVertices[i].normal.z;
        array[counter + 6] = mVertices[i].texCoord.x;
        array[counter + 7] = mVertices[i].texCoord.y;
        counter += 8;
    }
    return array;
}
