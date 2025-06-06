/**
 * @file IInputListener.h
 * @brief Declaration of the IInputListener interface, which defines a callback for input events.
 */

#pragma once
#include "SDL_events.h"

/**
 * @class IInputListener
 * @brief Interface for objects that want to receive input events.
 */
class IInputListener
{
public:
    /**
     * @brief Virtual destructor for IInputListener.
     */
    virtual ~IInputListener() = default;

    /**
     * @brief Callback method invoked when an input event occurs.
     * @param event Reference to the SDL event.
     */
    virtual void OnCall(SDL_Event& event) = 0;
};
