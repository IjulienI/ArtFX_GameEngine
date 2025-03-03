#pragma once
#include "SDL_events.h"

class IInputListener
{
public:
    virtual ~IInputListener() = default;
    virtual void OnCall(SDL_Event& event) = 0;
};