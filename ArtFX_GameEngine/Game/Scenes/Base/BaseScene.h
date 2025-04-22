#pragma once
#include "Core/Class/Scene/Scene.h"

class BaseScene : public Scene
{
public:
    BaseScene();
    ~BaseScene() override = default;
    
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() const override;
    void Load() override;
};
