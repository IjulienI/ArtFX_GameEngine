/**
 * @file EventDispatcher.cpp
 * @brief Implementation of the EventDispatcher class.
 */

#include "EventDispatcher.h"
#include <algorithm>

void EventDispatcher::BindEvent(IObserver* listener)
{
    events.push_back(listener);
}

void EventDispatcher::UnbindEvent(IObserver* listener)
{
    auto it = std::find(events.begin(), events.end(), listener);
    if (it != events.end())
    {
        iter_swap(it, events.end() -1);
        events.pop_back();
    }
}

void EventDispatcher::CallEvent()
{
    for (IObserver* event : events)
    {
        event->OnNotify();
    }
}
