#pragma once
#include <glew.h>
#include <vector>

#include "Shader.h"
#include "Math/Matrix4Row.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"

class ShaderProgram
{
private:
    unsigned int mId;

public:
    ShaderProgram();
    ~ShaderProgram() = default;
    void Unload();
    void Compose(std::vector<Shader*> shaders);

    unsigned int GetID();
    void Use();
    void setFloat(const GLchar* name, GLfloat value);
    void setInteger(const GLchar* name, GLint value);
    void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
    void setVector2f(const GLchar* name, const Vec2& value);
    void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
    void setVector3f(const GLchar* name, const Vec3& value);
    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setVector4f(const GLchar* name, const Vec4& value);
    void setMatrix4(const GLchar* name, const Matrix4& matrix);
    void setMatrix4Row(const GLchar* name, const Matrix4Row& matrix);    
};
