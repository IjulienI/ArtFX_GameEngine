#pragma once
#include <vector>

#include "Core/Render/Texture.h"
#include "Core/Render/Shader/Shader.h"
#include "Core/Render/Shader/ShaderProgram.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"

class VertexArray;

/**
 * @struct Vertex
 * @brief Represents a single vertex with position, normal, and texture coordinates.
 */
struct Vertex
{
public:
    /**
     * @brief Position of the vertex in 3D space.
     */
    Vec3 position;
    /**
     * @brief Normal vector at the vertex.
     */
    Vec3 normal;
    /**
     * @brief Texture coordinates of the vertex.
     */
    Vec2 texCoord;
};

/**
 * @struct Box
 * @brief Represents an axis-aligned bounding box in 3D space.
 */
struct Box
{
    /**
     * @brief Minimum corner of the box.
     */
    Vec3 min;
    /**
     * @brief Maximum corner of the box.
     */
    Vec3 max;

    /**
     * @brief Divides the box dimensions by a scalar.
     * @param scalar The scalar value to divide by.
     * @return Reference to the modified box.
     */
    Box& operator / (float scalar)
    {
        min /= scalar;
        max /= scalar;
        return *this;
    }
};

/**
 * @class Mesh
 * @brief Represents a 3D mesh, including its vertices, textures, shaders, and bounding information.
 */
class Mesh
{
private:
    /**
     * @brief List of textures associated with the mesh.
     */
    std::vector<Texture*> mTextures;
    /**
     * @brief Optional noise texture for the mesh.
     */
    Texture* mNoiseTexture = nullptr;
    /**
     * @brief List of vertices composing the mesh.
     */
    std::vector<Vertex> mVertices;
    /**
     * @brief Vertex array object for rendering.
     */
    VertexArray* mVertexArray;
    /**
     * @brief Vertex shader used by the mesh.
     */
    Shader mVertexShader;
    /**
     * @brief Fragment shader used by the mesh.
     */
    Shader mFragmentShader;
    /**
     * @brief Shader program used for rendering.
     */
    ShaderProgram mShaderProgram;
    /**
     * @brief Bounding sphere radius of the mesh.
     */
    float mRadius{};
    /**
     * @brief Axis-aligned bounding box of the mesh.
     */
    Box mBoundingBox;

    /**
     * @brief Calculates the bounding sphere radius of the mesh.
     */
    void CalculateRadius();
    /**
     * @brief Calculates the axis-aligned bounding box of the mesh.
     */
    void CalculateBoundingBox();
    
public:
    /**
     * @brief Default constructor.
     */
    Mesh();
    /**
     * @brief Constructs a mesh from a list of vertices.
     * @param vertices The vertices to initialize the mesh with.
     */
    Mesh(std::vector<Vertex> vertices);
    /**
     * @brief Destructor.
     */
    ~Mesh() = default;

    /**
     * @brief Unloads mesh resources.
     */
    void Unload();

    // Getter Setters    

    /**
     * @brief Adds a texture to the mesh.
     * @param pTexture Pointer to the texture to add.
     */
    void AddTexture(Texture* pTexture);
    /**
     * @brief Sets the shader program for the mesh.
     * @param pShaderProgram Reference to the shader program.
     */
    void SetShaderProgram(ShaderProgram& pShaderProgram);
    /**
     * @brief Sets the vertex array object for the mesh.
     * @param pVertexArray Pointer to the vertex array.
     */
    void SetVertexArray(VertexArray* pVertexArray);
    /**
     * @brief Gets the vertex array object.
     * @return Pointer to the vertex array.
     */
    VertexArray* GetVertexArray() const
    {
        return mVertexArray;
    }
    /**
     * @brief Gets the shader program.
     * @return Reference to the shader program.
     */
    ShaderProgram& GetShaderProgram()
    {
        return mShaderProgram;
    }
    /**
     * @brief Gets the number of vertices in the mesh.
     * @return Number of vertices.
     */
    int GetVerticesCount() const;
    /**
     * @brief Gets the list of vertices.
     * @return Vector of vertices.
     */
    std::vector<Vertex> GetVertices() const
    {
        return mVertices;
    }
    /**
     * @brief Gets a texture by index.
     * @param index Index of the texture.
     * @return Pointer to the texture.
     */
    Texture* GetTexture(size_t index);
    /**
     * @brief Gets the noise texture.
     * @return Pointer to the noise texture.
     */
    Texture* GetNoiseTexture() const
    {
        return mNoiseTexture;
    }
    /**
     * @brief Sets the noise texture.
     * @param pNoiseTexture Reference to the noise texture.
     */
    void SetNoiseTexture(Texture& pNoiseTexture)
    {
        mNoiseTexture = &pNoiseTexture;
    }
    /**
     * @brief Sets the bounding sphere radius.
     * @param radius The radius value.
     */
    void SetRadius(float radius);
    /**
     * @brief Gets the bounding sphere radius.
     * @return The radius value.
     */
    float GetRadius() const
    {
        return mRadius;
    }
    /**
     * @brief Converts the mesh's vertices to a float array.
     * @return Pointer to the float array.
     */
    float* ToVerticeArray();
    
    /**
     * @brief Gets the axis-aligned bounding box of the mesh.
     * @return The bounding box.
     */
    Box GetBoundingBox() const
    {
        return mBoundingBox;
    }
};
