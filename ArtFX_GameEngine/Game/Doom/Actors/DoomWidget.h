#pragma once
#include "Core/Class/Actor/Actor.h"

class DoomWidget : public Actor
{
private:
    SpriteComponent* sprite = nullptr;

public:
    DoomWidget();
    ~DoomWidget() override = default;
    void Start() override;
    void Update() override;
    void Destroy() override;
};
