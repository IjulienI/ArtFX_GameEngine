#pragma once

#include <fstream>
#include <string>

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

class Shader
{
protected:
    std::string mCode;
    unsigned int mId;
    ShaderType mType;

public:
    static const std::string SHADER_PATH;

    Shader();
    Shader(int id, std::string file, ShaderType shaderType);
    ~Shader();

    int GetId() const { return mId; }
    void Load(std::string fileName, ShaderType shaderType);

    std::string& GetCode() { return mCode; }
};
 