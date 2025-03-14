#include "ShaderProgram.h"

#include "Math/Matrix4.h"

ShaderProgram::ShaderProgram()
{
    mId = 0;
}

void ShaderProgram::Unload()
{
    glDeleteProgram(mId);
}

void ShaderProgram::Compose(std::vector<Shader*> shaders)
{
    mId = glCreateProgram();
    //now attach shaders to use to the program
    for (int s = 0; s < static_cast<int>(shaders.size()); s++) {
        glAttachShader(mId, shaders[s]->GetId());
    }
    //and link it
    glLinkProgram(mId);
    Use();
}

unsigned int ShaderProgram::GetID()
{
    return mId;
}

void ShaderProgram::Use()
{
    glUseProgram(mId);
}

void ShaderProgram::setFloat(const GLchar* name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(mId, name), value);
}
void ShaderProgram::setInteger(const GLchar* name, GLint value)
{
    glUniform1i(glGetUniformLocation(mId, name), value);
}
void ShaderProgram::setVector2f(const GLchar* name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(mId, name), x, y);
}
void ShaderProgram::setVector2f(const GLchar* name, const Vec2& value)
{
    glUniform2f(glGetUniformLocation(mId, name), value.x, value.y);
}
void ShaderProgram::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(mId, name), x, y, z);
}
void ShaderProgram::setVector3f(const GLchar* name, const Vec3& value)
{
    glUniform3f(glGetUniformLocation(mId, name), value.x, value.y, value.z);
}
void ShaderProgram::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(mId, name), x, y, z, w);
}
void ShaderProgram::setVector4f(const GLchar* name, const Vec4& value)
{
    glUniform4f(glGetUniformLocation(mId, name), value.x, value.y, value.z, value.w);
}
void ShaderProgram::setMatrix4(const GLchar* name, const Matrix4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_TRUE, matrix.GetAsFloatPtr());
}
void ShaderProgram::setMatrix4Row(const GLchar* name, const Matrix4Row& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, GL_TRUE, matrix.GetAsFloatPtr());
}

