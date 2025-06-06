/**
 * @file InputManager.cpp
 * @brief Implementation of the InputManager class, which manages input events and listeners.
 */

#include "InputManager.h"

/**
 * @brief Destructor for InputManager. Cleans up all input events.
 */
InputManager::~InputManager()
{
    std::map<SDL_Scancode, InputEvent*>::iterator it;
    for(it = mInputEvents.begin(); it != mInputEvents.end(); it++)
    {
        delete (it->second);
    }
    mInputEvents.clear();
}

/**
 * @brief Gets the singleton instance of the InputManager.
 * @return Reference to the InputManager instance.
 */
InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

/**
 * @brief Handles SDL input events and dispatches them to the appropriate listeners.
 * @param event Reference to the SDL event.
 */
void InputManager::HandleInputs(SDL_Event& event)
{
    std::map<SDL_Scancode, InputEvent*>::iterator it = mInputEvents.find(event.key.keysym.scancode);
    if(it != mInputEvents.end())
    {
        (*it).second->CallEvent(event);        
    }
}

/**
 * @brief Binds an input listener to a specific key.
 * @param keyCode SDL scancode of the key.
 * @param listener Pointer to the input listener to bind.
 */
void InputManager::BindTo(SDL_Scancode keyCode, IInputListener* listener)
{
    size_t hasKey = mInputEvents.count(keyCode);
    if(hasKey == 0)
    {
        mInputEvents[keyCode] = new InputEvent();
    }
    mInputEvents[keyCode]->BindEvent(listener);
}
