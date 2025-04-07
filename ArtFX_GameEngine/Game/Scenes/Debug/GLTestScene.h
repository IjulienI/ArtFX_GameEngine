#pragma once
#include "Core/Class/Scene/Scene.h"
#include "Core/Render/Shader/Shader.h"
#include "Core/Render/Shader/ShaderProgram.h"

class GLTestScene : public Scene
{
private:
    Shader* mVertexShader = new Shader();
    Shader* mFragmentShader = new Shader();
    ShaderProgram mSimpleProgram;
public:
    GLTestScene();
    ~GLTestScene() override = default;
    
    void Start() override;
    void Update() override;
    void Close() const override;
    void Load() override;
};
