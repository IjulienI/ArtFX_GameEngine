﻿#pragma once
#include "Core/Class/Scene/Scene.h"

class GLTestScene : public Scene
{
public:
    GLTestScene();
    ~GLTestScene() override = default;
    
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() const override;
    void Load() override;
};
