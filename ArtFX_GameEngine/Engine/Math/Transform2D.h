#pragma once
#include "../../Engine/Math/Vec2.h"

class Transform2D
{
public:
    Vec2 position;
    Vec2 scale;
    float rotation;

public:
    Transform2D(Vec2 position, Vec2 scale, float rotation);
    Transform2D();

public:
    Vec2 GetPosition();
    Vec2 GetScale();
    float GetRotation();

    Vec2 Right();
    Vec2 Up();  
};
