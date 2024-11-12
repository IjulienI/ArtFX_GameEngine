#pragma once
#include <SDL_rect.h>
#include "Vec2.h"

struct Rectangle
{
    Vec2 position;
    Vec2 dimensions;

    Rectangle(float x, float y, float w, float h) : position({ x, y }), dimensions({ w, h }) {

    }

    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y) };
    }
};
