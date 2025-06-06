#include "Rectangle.h"

const Rectangle Rectangle::NullRect{ {0.0f,0.0f}, {0.0f, 0.0f}};


Rectangle::Rectangle(Vec2 pPosition, Vec2 pDimensions)
{
    position = pPosition;
    dimensions = pDimensions;
}
