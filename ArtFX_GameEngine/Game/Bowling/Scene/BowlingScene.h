#pragma once
#include "Bowling/BowlingState.h"
#include "Core/Class/Scene/Scene.h"

class Player;

class BowlingScene : public Scene
{
protected:
    Player* mPlayer = nullptr;

    void SetUpBoxCollisions(int i);

public:
    BowlingScene();
    ~BowlingScene() override = default;
    
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() const override;
    void Load() override;
    
};
