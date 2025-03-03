#include "Transform2D.h"

#include "Maths.h"

Transform2D::Transform2D(Vec2 position, Vec2 scale, float rotation) : position(position), scale(scale), rotation(rotation)
{
}

Transform2D::Transform2D() : position({0.0f, 0.0f}), scale({1.0f, 1.0f}), rotation(0.0f)
{
}

Vec2 Transform2D::GetPosition()
{
    return position;
}

Vec2 Transform2D::GetScale()
{
    return scale;
}

float Transform2D::GetRotation()
{
    return rotation;
}

Vec2 Transform2D::Right()
{
    return Vec2(Maths::Cos(rotation), -Maths::Sin(rotation));
}

Vec2 Transform2D::Up()
{
    return Vec2(Maths::Sin(rotation), -Maths::Cos(rotation));
}
