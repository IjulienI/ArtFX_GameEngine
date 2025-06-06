/**
 * @file Shader.h
 * @brief Declaration of the Shader class, which represents an OpenGL shader.
 */

#pragma once

#include <fstream>
#include <string>

/**
 * @enum ShaderType
 * @brief Enum representing different types of shaders.
 */
enum ShaderType
{
    VERTEX,                /**< Vertex shader. */
    FRAGMENT,              /**< Fragment shader. */
    TESSELLATION_CONTROL,  /**< Tessellation control shader. */
    TESSELLATION_EVALUATION, /**< Tessellation evaluation shader. */
    GEOMETRY               /**< Geometry shader. */
};

/**
 * @class Shader
 * @brief Represents an OpenGL shader, including its source code and type.
 */
class Shader
{
protected:
    /**
     * @brief Source code of the shader.
     */
    std::string mCode;

    /**
     * @brief ID of the shader in OpenGL.
     */
    unsigned int mId;

    /**
     * @brief Type of the shader.
     */
    ShaderType mType;

public:
    /**
     * @brief Path to the shader files.
     */
    static const std::string SHADER_PATH;

    /**
     * @brief Default constructor for Shader.
     */
    Shader();

    /**
     * @brief Constructs a Shader with a given ID, file, and type.
     * @param id OpenGL shader ID.
     * @param file Path to the shader file.
     * @param shaderType Type of the shader.
     */
    Shader(int id, std::string file, ShaderType shaderType);

    /**
     * @brief Destructor for Shader.
     */
    ~Shader();

    /**
     * @brief Gets the OpenGL ID of the shader.
     * @return Shader ID.
     */
    int GetId() const { return mId; }

    /**
     * @brief Loads the shader source code from a file and compiles it.
     * @param fileName Path to the shader file.
     * @param shaderType Type of the shader.
     */
    void Load(std::string fileName, ShaderType shaderType);

    /**
     * @brief Gets the source code of the shader.
     * @return Reference to the shader source code.
     */
    std::string& GetCode() { return mCode; }
};
