#pragma once
#include "Core/Class/Scene/Scene.h"

class BowlingScene : public Scene
{
private:
    const int PIST_AMOUNT = 12;
    const float PIST_OFFSET = 6.33f;
    
public:
    BowlingScene();
    ~BowlingScene() override = default;
    
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() const override;
    void Load() override;
    
};
