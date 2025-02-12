#include "Transform2D.h"

Transform2D::Transform2D(Vec2 position, Vec2 scale, Vec2 rotation) : position(position), scale(scale), rotation(rotation)
{
}

Transform2D::Transform2D() : position({0.0f, 0.0f}), scale({1.0f, 1.0f}), rotation({0.0f, 0.0f})
{
}
