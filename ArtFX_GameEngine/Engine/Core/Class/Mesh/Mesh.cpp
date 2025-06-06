/**
 * @file Mesh.cpp
 * @brief Implementation of the Mesh class, representing a 3D mesh.
 */

#include "Mesh.h"
#include <algorithm>
#include "Core/Render/Asset.h"
#include "Core/Render/OpenGL/VertexArray.h"
#include "Debug/Log.h"

/// Default constructor for Mesh.
Mesh::Mesh() : mVertexArray(nullptr)
{
}

/// Constructs a Mesh from a list of vertices.
/// @param vertices The vertices to initialize the mesh with.
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

/// Unloads mesh resources and deletes the vertex array.
void Mesh::Unload()
{
    delete mVertexArray;
    mVertexArray = nullptr;
}

/// Adds a texture to the mesh.
/// @param pTexture Pointer to the texture to add.
void Mesh::AddTexture(Texture* pTexture)
{
    if (!mTextures.empty())
    {        
        if (mTextures[0] == &Asset::GetTexture("BaseTexture"))
        {
            mTextures.clear();
        }
        for (auto& mTexture : mTextures)
        {
            if (mTexture == pTexture) return;
        }
    }
    mTextures.emplace_back(pTexture);
}

/// Sets the shader program for the mesh.
/// @param pShaderProgram Reference to the shader program.
void Mesh::SetShaderProgram(ShaderProgram& pShaderProgram)
{
    mShaderProgram = pShaderProgram;
}

/// Sets the vertex array object for the mesh.
/// @param pVertexArray Pointer to the vertex array.
void Mesh::SetVertexArray(VertexArray* pVertexArray)
{
    mVertexArray = pVertexArray;
}

/// Returns the number of vertices in the mesh.
/// @return Number of vertices.
int Mesh::GetVerticesCount() const
{
    return static_cast<int>(mVertices.size());
}

/// Returns the texture at the specified index.
/// @param index Index of the texture.
/// @return Pointer to the texture, or nullptr if out of range.
Texture* Mesh::GetTexture(size_t index)
{
    if (index > mTextures.size() -1)
    {
        return nullptr;
    }
    return mTextures[index];
}

/// Sets the bounding sphere radius of the mesh.
/// @param radius The radius value.
void Mesh::SetRadius(float radius)
{
    mRadius = radius;
}

/// Converts the mesh's vertices to a float array.
/// @return Pointer to the float array (caller must delete[]).
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

/// Calculates the bounding sphere radius of the mesh.
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

/// Calculates the axis-aligned bounding box of the mesh.
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
