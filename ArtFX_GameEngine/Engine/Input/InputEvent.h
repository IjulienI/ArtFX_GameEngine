/**
 * @file InputEvent.h
 * @brief Declaration of the InputEvent class, which manages input event listeners and dispatches events.
 */

#pragma once
#include <SDL_events.h>
#include <vector>

class IInputListener;

/**
 * @class InputEvent
 * @brief Manages a list of input listeners and dispatches SDL events to them.
 */
class InputEvent
{
private:
    /**
     * @brief List of registered input listeners.
     */
    std::vector<IInputListener*> mListeners;

public:
    /**
     * @brief Default constructor for InputEvent.
     */
    InputEvent() = default;

    /**
     * @brief Destructor for InputEvent.
     */
    ~InputEvent();

    /**
     * @brief Registers an input listener to receive events.
     * @param listener Pointer to the input listener to register.
     */
    void BindEvent(IInputListener* listener);

    /**
     * @brief Unregisters an input listener from receiving events.
     * @param listener Pointer to the input listener to unregister.
     */
    void UnBindEvent(IInputListener* listener);

    /**
     * @brief Dispatches an SDL event to all registered listeners.
     * @param event Reference to the SDL event to dispatch.
     */
    void CallEvent(SDL_Event& event);
};
