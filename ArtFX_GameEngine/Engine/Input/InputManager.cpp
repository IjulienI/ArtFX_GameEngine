#include "InputManager.h"

InputManager::~InputManager()
{
    std::map<SDL_Keycode, InputEvent*>::iterator it;
    for(it = mInputEvents.begin() ; it !=mInputEvents.end() ; it ++)
    {
        delete (it->second);
    }
    mInputEvents.clear();
}

InputManager& InputManager::Instance()
{
}

void InputManager::HandleInputs(SDL_Event& event)
{
}

void InputManager::BindTo(SDL_Keycode keyCode, IInputListener* listener)
{
}
