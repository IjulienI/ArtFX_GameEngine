#include "Mesh.h"

#include <algorithm>

#include "Core/Render/Asset.h"
#include "Core/Render/OpenGL/VertexArray.h"

/**
 * @file Mesh.cpp
 * @brief Implémentation de la classe Mesh, représentant un maillage 3D.
 */

Mesh::Mesh() : mVertexArray(nullptr)
{
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
    CalculateRadius();
    CalculateBoundingBox();
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

void Mesh::SetShaderProgram(ShaderProgram& pShaderProgram)
{
    mShaderProgram = pShaderProgram;
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

/**
 * @brief Calcule le rayon englobant du maillage.
 */
void Mesh::CalculateRadius()
{

    if (mVertices.empty())
    {
        mRadius = 0.0f;
        return;
    }
    
    Vec3 center = Vec3::zero;

    for (const Vertex& vertex : mVertices)
    {
        center += vertex.position;
    }
    center /= static_cast<float>(mVertices.size());
    
    float maxDistanceSquared = 0.0f;
    for (const Vertex& vertex : mVertices)
    {
        float distanceSquared = (vertex.position - center).LengthSq();
        maxDistanceSquared = std::max(distanceSquared, maxDistanceSquared);
    }

    mRadius = sqrtf(maxDistanceSquared);
}

/**
 * @brief Calcule la boîte englobante du maillage.
 */
void Mesh::CalculateBoundingBox()
{
    Box boundingBox;
    float maxFloat = std::numeric_limits<float>::max();
    float minFloat = std::numeric_limits<float>::lowest();
    boundingBox.min = Vec3(maxFloat, maxFloat, maxFloat);
    boundingBox.max = Vec3(minFloat, minFloat, minFloat);

    for (const auto& vertex : mVertices)
    {
        boundingBox.min.x = std::min(boundingBox.min.x, vertex.position.x);
        boundingBox.min.y = std::min(boundingBox.min.y, vertex.position.y);
        boundingBox.min.z = std::min(boundingBox.min.z, vertex.position.z);

        boundingBox.max.x = std::max(boundingBox.max.x, vertex.position.x);
        boundingBox.max.y = std::max(boundingBox.max.y, vertex.position.y);
        boundingBox.max.z = std::max(boundingBox.max.z, vertex.position.z);
    }

    mBoundingBox = boundingBox;
}

