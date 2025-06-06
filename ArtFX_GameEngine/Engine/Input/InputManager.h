/**
 * @file InputManager.h
 * @brief Declaration of the InputManager class, which manages input events and listeners.
 */

#pragma once

#include <map>
#include "InputEvent.h"

/**
 * @class InputManager
 * @brief Singleton class that manages input events and dispatches them to registered listeners.
 */
class InputManager
{
    /**
     * @brief Map of input events, indexed by SDL scancode.
     */
    std::map<SDL_Scancode, InputEvent*> mInputEvents;

public:
    /**
     * @brief Default constructor for InputManager.
     */
    InputManager() = default;

    /**
     * @brief Destructor for InputManager. Cleans up all input events.
     */
    ~InputManager();

    /**
     * @brief Deleted copy constructor.
     */
    InputManager(const InputManager&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    InputManager& operator=(const InputManager&) = delete;

    /**
     * @brief Gets the singleton instance of the InputManager.
     * @return Reference to the InputManager instance.
     */
    static InputManager& Instance();

    /**
     * @brief Handles SDL input events and dispatches them to the appropriate listeners.
     * @param event Reference to the SDL event.
     */
    void HandleInputs(SDL_Event& event);

    /**
     * @brief Binds an input listener to a specific key.
     * @param keyCode SDL scancode of the key.
     * @param listener Pointer to the input listener to bind.
     */
    void BindTo(SDL_Scancode keyCode, IInputListener* listener);
};
