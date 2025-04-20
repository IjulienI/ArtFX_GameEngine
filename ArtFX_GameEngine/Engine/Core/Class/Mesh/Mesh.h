#pragma once
#include <vector>

#include "Core/Render/Texture.h"
#include "Core/Render/Shader/Shader.h"
#include "Core/Render/Shader/ShaderProgram.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"

constexpr float cubeVertices[] = {
    -0.5, -0.5, -0.5, 0, 0 ,
    0.5, -0.5, -0.5, 1, 0 ,
    -0.5, 0.5, -0.5,0, -1 ,
    0.5, 0.5, -0.5, 1, -1 ,
    -0.5, 0.5, 0.5, 0, -1 ,
    0.5, 0.5, 0.5, 1, -1 ,
    -0.5, -0.5, 0.5, 0, 0 ,
    0.5, -0.5, 0.5, 1, 0 ,
    -0.5, 0.5, -0.5, 0, -1 ,
    0.5, -0.5, -0.5, 1, 0 ,
    -0.5, 0.5, -0.5, 0, -1 ,
    0.5, 0.5, -0.5, 1, -1 ,
    -0.5, 0.5, 0.5, 0, -1 ,
    -0.5, 0.5, 0.5, 0, -1 ,
    0.5, 0.5, 0.5, 1, -1 ,
    -0.5, -0.5, 0.5, 0, 0 ,
    -0.5, -0.5, 0.5, 0, 0 ,
    0.5, -0.5, 0.5, 1, 0 ,
    -0.5, -0.5, -0.5, 0, 0 ,
    0.5, -0.5, -0.5, 1, 0 ,
    0.5, -0.5, -0.5, 1, 0 ,
    0.5, -0.5, 0.5, 1, 0 ,
    0.5, 0.5, -0.5, 1, -1 ,
    0.5, 0.5, 0.5, 1, -1 ,
    -0.5, -0.5, 0.5, 0, 0 ,
    -0.5, -0.5, -0.5, 0, 0 ,
    -0.5, 0.5, 0.5, 0, -1 ,
    -0.5, 0.5, -0.5, 0, -1
 };

constexpr unsigned int cubeIndices[] = {
    2, 1, 0 ,
     3, 9, 8 ,
     4, 11, 10 ,
     5, 11, 12 ,
     6, 14, 13 ,
     7, 14, 15 ,
     18, 17, 16 ,
     19, 17, 18 ,
     22, 21, 20 ,
     23, 21, 22 ,
     26, 25, 24 ,
     27, 25, 26
 };



class VertexArray;

struct Vertex
{
public:
    Vec3 position;
    Vec3 normal;
    Vec2 texCoord;
};

class Mesh
{
private:
    std::vector<Texture*> mTextures;
    std::vector<Vertex> mVertices;
    VertexArray* mVertexArray;
    Shader mVertexShader, mFragmentShader;
    ShaderProgram mShaderProgram;
    
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices);
    ~Mesh() = default;

    void Unload();

    //Getter Setters    
    void AddTexture(Texture* pTexture);
    void SetShaderProgram(ShaderProgram*& pShaderProgram);
    void SetVertexArray(VertexArray* pVertexArray);
    VertexArray* GetVertexArray()
    {
        return mVertexArray;
    }
    ShaderProgram& GetShaderProgram()
    {
        return mShaderProgram;
    }
    int GetVerticesCount() const;
    Texture* GetTexture(size_t index);
};
