#pragma once
#include "Core/Class/Scene/Scene.h"

class DoomScene : public Scene
{
public:
    DoomScene();
    ~DoomScene() override = default;
    
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() const override;
    void Load() override;
};
