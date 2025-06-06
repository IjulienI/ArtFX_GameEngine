/**
 * @file Shader.cpp
 * @brief Implementation of the Shader class, which represents an OpenGL shader.
 */

#include "Shader.h"

#include <glew.h>
#include "Debug/Log.h"

/**
 * @brief Path to the directory containing shader files.
 */
const std::string Shader::SHADER_PATH = "Shaders/";

/**
 * @brief Default constructor for Shader.
 * Initializes the shader ID to 0, code to an empty string, and type to VERTEX.
 */
Shader::Shader() : mId(0), mCode(""), mType(VERTEX)
{
}

/**
 * @brief Constructs a Shader with a given ID, file, and type.
 * @param id OpenGL shader ID.
 * @param file Path to the shader file.
 * @param shaderType Type of the shader.
 */
Shader::Shader(int id, std::string file, ShaderType shaderType) : mId(id), mCode(file), mType(shaderType)
{
}

/**
 * @brief Destructor for Shader.
 * Cleans up resources associated with the shader.
 */
Shader::~Shader()
{
}

/**
 * @brief Loads the shader source code from a file and compiles it.
 * @param fileName Path to the shader file.
 * @param shaderType Type of the shader.
 */
void Shader::Load(std::string fileName, ShaderType shaderType)
{
    mType = shaderType;
    std::ifstream myFile;
    myFile.open(SHADER_PATH + fileName);
    if (myFile.fail()) {
        Log::Error(LogType::Video, "Error - failed to open " + fileName);
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
    case VERTEX:
        {
            mId = glCreateShader(GL_VERTEX_SHADER);
            break;
        }
    case FRAGMENT:
        {
            mId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        }
    case TESSELLATION_CONTROL:
        {
            mId = glCreateShader(GL_TESS_CONTROL_SHADER);
            break;
        }
    case TESSELLATION_EVALUATION:
        {
            mId = glCreateShader(GL_TESS_EVALUATION_SHADER);
            break;
        }
    case GEOMETRY:
        {
            mId = glCreateShader(GL_GEOMETRY_SHADER);
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
