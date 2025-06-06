/**
 * @file ShaderProgram.cpp
 * @brief Implementation of the ShaderProgram class, which manages OpenGL shader programs.
 */

#include "ShaderProgram.h"
#include "Math/Matrix4.h"

/**
 * @brief Constructs a ShaderProgram object and initializes its ID to 0.
 */
ShaderProgram::ShaderProgram()
{
    mId = 0;
}

/**
 * @brief Unloads the shader program from OpenGL by deleting its ID.
 */
void ShaderProgram::Unload()
{
    glDeleteProgram(mId);
}

/**
 * @brief Composes the shader program by attaching and linking multiple shaders.
 * @param shaders Vector of pointers to Shader objects.
 */
void ShaderProgram::Compose(std::vector<Shader*> shaders)
{
    mId = glCreateProgram();
    // Attach shaders to the program
    for (int s = 0; s < static_cast<int>(shaders.size()); s++) {
        glAttachShader(mId, shaders[s]->GetId());
    }
    // Link the program
    glLinkProgram(mId);
    Use();
}

/**
 * @brief Gets the ID of the shader program.
 * @return OpenGL program ID.
 */
unsigned int ShaderProgram::GetID()
{
    return mId;
}

/**
 * @brief Activates the shader program for rendering.
 */
void ShaderProgram::Use()
{
    glUseProgram(mId);
}

/**
 * @brief Sets a float uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param value Float value to set.
 */
void ShaderProgram::setFloat(const GLchar* name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(mId, name), value);
}

/**
 * @brief Sets an integer uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param value Integer value to set.
 */
void ShaderProgram::setInteger(const GLchar* name, GLint value)
{
    glUniform1i(glGetUniformLocation(mId, name), value);
}

/**
 * @brief Sets a 2D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param x X component of the vector.
 * @param y Y component of the vector.
 */
void ShaderProgram::setVector2f(const GLchar* name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(mId, name), x, y);
}

/**
 * @brief Sets a 2D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param value Vec2 object representing the vector.
 */
void ShaderProgram::setVector2f(const GLchar* name, const Vec2& value)
{
    glUniform2f(glGetUniformLocation(mId, name), value.x, value.y);
}

/**
 * @brief Sets a 3D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param x X component of the vector.
 * @param y Y component of the vector.
 * @param z Z component of the vector.
 */
void ShaderProgram::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(mId, name), x, y, z);
}

/**
 * @brief Sets a 3D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param value Vec3 object representing the vector.
 */
void ShaderProgram::setVector3f(const GLchar* name, const Vec3& value)
{
    glUniform3f(glGetUniformLocation(mId, name), value.x, value.y, value.z);
}

/**
 * @brief Sets a 4D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param x X component of the vector.
 * @param y Y component of the vector.
 * @param z Z component of the vector.
 * @param w W component of the vector.
 */
void ShaderProgram::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(mId, name), x, y, z, w);
}

/**
 * @brief Sets a 4D vector uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param value Vec4 object representing the vector.
 */
void ShaderProgram::setVector4f(const GLchar* name, const Vec4& value)
{
    glUniform4f(glGetUniformLocation(mId, name), value.x, value.y, value.z, value.w);
}

/**
 * @brief Sets a 4x4 matrix uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param matrix Matrix4 object representing the matrix.
 */
void ShaderProgram::setMatrix4(const GLchar* name, const Matrix4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_TRUE, matrix.GetAsFloatPtr());
}

/**
 * @brief Sets a 4x4 matrix uniform variable in the shader program.
 * @param name Name of the uniform variable.
 * @param matrix Matrix4Row object representing the matrix.
 */
void ShaderProgram::setMatrix4Row(const GLchar* name, const Matrix4Row& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_TRUE, matrix.GetAsFloatPtr());
}
