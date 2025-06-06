/**
 * @file ShaderProgram.h
 * @brief Declaration of the ShaderProgram class, which manages OpenGL shader programs.
 */

#pragma once
#include <glew.h>
#include <vector>
#include "Shader.h"
#include "Math/Matrix4Row.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"

/**
 * @class ShaderProgram
 * @brief Represents an OpenGL shader program composed of multiple shaders.
 */
class ShaderProgram
{
private:
    /**
     * @brief ID of the OpenGL shader program.
     */
    unsigned int mId;

public:
    /**
     * @brief Constructs a ShaderProgram object.
     */
    ShaderProgram();

    /**
     * @brief Destructor for ShaderProgram.
     */
    ~ShaderProgram() = default;

    /**
     * @brief Unloads the shader program from OpenGL.
     */
    void Unload();

    /**
     * @brief Composes the shader program by linking multiple shaders.
     * @param shaders Vector of pointers to Shader objects.
     */
    void Compose(std::vector<Shader*> shaders);

    /**
     * @brief Gets the ID of the shader program.
     * @return OpenGL program ID.
     */
    unsigned int GetID();

    /**
     * @brief Activates the shader program for rendering.
     */
    void Use();

    /**
     * @brief Sets a float uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param value Float value to set.
     */
    void setFloat(const GLchar* name, GLfloat value);

    /**
     * @brief Sets an integer uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param value Integer value to set.
     */
    void setInteger(const GLchar* name, GLint value);

    /**
     * @brief Sets a 2D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     */
    void setVector2f(const GLchar* name, GLfloat x, GLfloat y);

    /**
     * @brief Sets a 2D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param value Vec2 object representing the vector.
     */
    void setVector2f(const GLchar* name, const Vec2& value);

    /**
     * @brief Sets a 3D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Sets a 3D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param value Vec3 object representing the vector.
     */
    void setVector3f(const GLchar* name, const Vec3& value);

    /**
     * @brief Sets a 4D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     * @param w W component of the vector.
     */
    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    /**
     * @brief Sets a 4D vector uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param value Vec4 object representing the vector.
     */
    void setVector4f(const GLchar* name, const Vec4& value);

    /**
     * @brief Sets a 4x4 matrix uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param matrix Matrix4 object representing the matrix.
     */
    void setMatrix4(const GLchar* name, const Matrix4& matrix);

    /**
     * @brief Sets a 4x4 matrix uniform variable in the shader program.
     * @param name Name of the uniform variable.
     * @param matrix Matrix4Row object representing the matrix.
     */
    void setMatrix4Row(const GLchar* name, const Matrix4Row& matrix);
};
