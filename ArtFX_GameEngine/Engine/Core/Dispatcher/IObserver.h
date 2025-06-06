/**
 * @file IObserver.h
 * @brief Interface for observer classes used in the event dispatching system.
 */

#pragma once

/**
 * @class IObserver
 * @brief Interface for objects that want to receive notifications from an EventDispatcher.
 */
class IObserver
{
    public:
    /**
     * @brief Default constructor.
     */
    IObserver() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IObserver() = default;

    /**
     * @brief Called when the observer is notified by the dispatcher.
     */
    virtual void OnNotify() = 0;
};
