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

    inline bool HandleCollision(Rectangle* b)
    {
        float xMinA =  position.x;
        float yMinA =  position.y;
        float xMaxA =  position.x + dimensions.x;
        float yMaxA =  position.y + dimensions.y;
        float xMinB =  b->position.x;
        float yMinB =  b->position.y;
        float xMaxB =  b->position.x + b->dimensions.x;
        float yMaxB =  b->position.y + b->dimensions.y;

        return(!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
    }
};
