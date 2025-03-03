#include "InputEvent.h"

#include "IInputListener.h"


InputEvent::~InputEvent()
{
    mListeners.clear();
}

void InputEvent::BindEvent(IInputListener* listener)
{
    mListeners.push_back(listener);
}

void InputEvent::UnBindEvent(IInputListener* listener)
{
    std::vector<IInputListener*>::iterator it;
    if((it = std::find(mListeners.begin(), mListeners.end(), listener)) != mListeners.end())
    {
        mListeners.erase(it);
    }
}

void InputEvent::CallEvent(SDL_Event& event)
{
    for(IInputListener* listener : mListeners)
    {
        listener->OnCall(event);
    }
}
