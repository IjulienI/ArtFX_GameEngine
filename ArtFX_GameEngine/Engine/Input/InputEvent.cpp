/**
 * @file InputEvent.cpp
 * @brief Implementation of the InputEvent class, which manages input event listeners and dispatches events.
 */

#include "InputEvent.h"
#include "IInputListener.h"

/**
 * @brief Destructor for InputEvent. Clears all registered listeners.
 */
InputEvent::~InputEvent()
{
    mListeners.clear();
}

/**
 * @brief Registers an input listener to receive events.
 * @param listener Pointer to the input listener to register.
 */
void InputEvent::BindEvent(IInputListener* listener)
{
    mListeners.push_back(listener);
}

/**
 * @brief Unregisters an input listener from receiving events.
 * @param listener Pointer to the input listener to unregister.
 */
void InputEvent::UnBindEvent(IInputListener* listener)
{
    std::vector<IInputListener*>::iterator it;
    if((it = std::find(mListeners.begin(), mListeners.end(), listener)) != mListeners.end())
    {
        mListeners.erase(it);
    }
}

/**
 * @brief Dispatches an SDL event to all registered listeners.
 * @param event Reference to the SDL event to dispatch.
 */
void InputEvent::CallEvent(SDL_Event& event)
{
    for(IInputListener* listener : mListeners)
    {
        listener->OnCall(event);
    }
}
