#pragma once
#include "Core/Class/Scene/Scene.h"

class DebugCollisionScene : public Scene
{
public:
    DebugCollisionScene();
    ~DebugCollisionScene() override = default;
    
    void Start() override;
    void OnInput(SDL_Event) override;
};
