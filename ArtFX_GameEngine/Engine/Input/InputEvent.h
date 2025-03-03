#pragma once
#include <SDL_events.h>
#include <vector>

class IInputListener;

class InputEvent
{
private:
    std::vector<IInputListener*> mListeners;
public:
    InputEvent() = default;
    ~InputEvent();
    
    void BindEvent(IInputListener* listener);
    void UnBindEvent(IInputListener* listener);
    void CallEvent(SDL_Event& event);
    
};
