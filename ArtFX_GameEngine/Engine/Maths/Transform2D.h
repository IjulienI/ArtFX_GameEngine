#pragma once
#include "../../Vec2.h"

class Transform2D
{
public:
    Vec2 position = {0.0f, 0.0f};
    Vec2 scale = {1.0f, 1.0f};
    Vec2 rotation = {0.0f, 0.0f};

public:
    Transform2D(Vec2 position, Vec2 scale, Vec2 rotation);
    Transform2D();
    
};
