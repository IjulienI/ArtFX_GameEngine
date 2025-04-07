#include "Shader.h"

#include <glew.h>
#include "Debug/Log.h"

const std::string Shader::SHADER_PATH = "Engine/Core/Render/Shader/";

Shader::Shader() : mId(0), mCode(""), mType(VERTEX)
{
}

Shader::Shader(int id, std::string file, ShaderType shaderType) : mId(id), mCode(file), mType(shaderType)
{
}

Shader::~Shader()
{
}

void Shader::Load(std::string fileName, ShaderType shaderType)
{
    mType = shaderType;
    std::ifstream myFile;
    myFile.open(SHADER_PATH + fileName);
    if (myFile.fail()) {
        Log::Error(LogType::Video, "Error - failed to open " + fileName );;
    }
    std::string fileText = "";
    std::string line = "";
    while (getline(myFile, line)) {
        fileText += line + '\n';
    }
  
    myFile.close();
    mCode = fileText;
  
    switch (mType)
    {
    case VERTEX: {
            mId = glCreateShader(GL_VERTEX_SHADER);
            break;
    }
    case FRAGMENT: {
            mId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    default:
        {
            Log::Error(LogType::Render, "This shader type has not yet been implemented.");
            mId = glCreateShader(GL_VERTEX_SHADER);
            break;
        }
    }
    const char* source = mCode.c_str();
    glShaderSource(mId, 1, &source,  NULL);
    glCompileShader(mId);
}
