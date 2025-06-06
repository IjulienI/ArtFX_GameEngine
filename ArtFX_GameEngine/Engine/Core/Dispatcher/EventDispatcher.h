/**
 * @file EventDispatcher.h
 * @brief Declaration of the EventDispatcher class, which manages event listeners and notifications.
 */

#pragma once

#include <vector>
#include "IObserver.h"

/**
 * @class EventDispatcher
 * @brief Manages a list of observers and notifies them of events.
 */
class EventDispatcher
{
private:
    /**
     * @brief List of registered observers.
     */
    std::vector<IObserver*> events;

public:
    /**
     * @brief Default constructor.
     */
    EventDispatcher() = default;

    /**
     * @brief Registers an observer to receive event notifications.
     * @param listener Pointer to the observer to register.
     */
    void BindEvent(IObserver* listener);

    /**
     * @brief Unregisters an observer from receiving event notifications.
     * @param listener Pointer to the observer to unregister.
     */
    void UnbindEvent(IObserver* listener);

    /**
     * @brief Notifies all registered observers of the event.
     */
    void CallEvent();    
};

