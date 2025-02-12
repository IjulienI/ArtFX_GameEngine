#pragma once

#include <vector>
#include "IObserver.h"

class EventDispatcher
{
private:
    std::vector<IObserver*> events;

public:
    EventDispatcher() = default;

    void BindEvent(IObserver* listener);
    void UnbindEvent(IObserver* listener);
    void CallEvent();
    
};
