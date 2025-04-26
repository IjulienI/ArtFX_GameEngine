#pragma once
#include <vector>

#include "Core/Render/Texture.h"
#include "Core/Render/Shader/Shader.h"
#include "Core/Render/Shader/ShaderProgram.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"

class VertexArray;

struct Vertex
{
public:
    Vec3 position;
    Vec3 normal;
    Vec2 texCoord;
};

struct Box
{
    Vec3 min;
    Vec3 max;

    Box& operator / (float scalar)
    {
        min /= scalar;
        max /= scalar;
        return *this;
    }
};

class Mesh
{
private:
    std::vector<Texture*> mTextures;
    std::vector<Vertex> mVertices;
    VertexArray* mVertexArray;
    Shader mVertexShader, mFragmentShader;
    ShaderProgram mShaderProgram;
    float mRadius{};
    Box mBoundingBox;

    void CalculateRadius();
    void CalculateBoundingBox();
    
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices);
    ~Mesh() = default;

    void Unload();

    //Getter Setters    
    void AddTexture(Texture* pTexture);
    void SetShaderProgram(ShaderProgram*& pShaderProgram);
    void SetVertexArray(VertexArray* pVertexArray);
    VertexArray* GetVertexArray() const
    {
        return mVertexArray;
    }
    ShaderProgram& GetShaderProgram()
    {
        return mShaderProgram;
    }
    int GetVerticesCount() const;
    std::vector<Vertex> GetVertices() const
    {
        return mVertices;
    }
    Texture* GetTexture(size_t index);
    void SetRadius(float radius);
    float GetRadius() const
    {
        return mRadius;
    }
    float* ToVerticeArray();
    
    Box GetBoundingBox() const
    {
        return mBoundingBox;
    }
};
