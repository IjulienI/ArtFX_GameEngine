#pragma once
#include "../../Vec2.h"

class Transform2D
{
public:
    Vec2 position;
    Vec2 scale;
    Vec2 rotation;

public:
    Transform2D(Vec2 position, Vec2 scale, Vec2 rotation);
    Transform2D();
    
};
