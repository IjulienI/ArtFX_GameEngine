#include "InputManager.h"

InputManager::~InputManager()
{
    std::map<SDL_Scancode, InputEvent*>::iterator it;
    for(it = mInputEvents.begin() ; it != mInputEvents.end() ; it ++)
    {
        delete (it->second);
    }
    mInputEvents.clear();
}

InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

void InputManager::HandleInputs(SDL_Event& event)
{
    std::map<SDL_Scancode, InputEvent*>::iterator it = mInputEvents.find(event.key.keysym.scancode);
    if(it != mInputEvents.end())
    {
        (*it).second->CallEvent(event);
    }
}

void InputManager::BindTo(SDL_Scancode keyCode, IInputListener* listener)
{
    size_t hasKey = mInputEvents.count(keyCode);
    if(hasKey == 0)
    {
        mInputEvents[keyCode] = new InputEvent();
    }
    mInputEvents[keyCode]->BindEvent(listener);
}
