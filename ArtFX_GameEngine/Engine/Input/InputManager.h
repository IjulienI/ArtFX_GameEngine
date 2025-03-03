#pragma once
#include <map>
#include <SDL_keycode.h>

#include "InputEvent.h"

class InputManager
{
    std::map<SDL_Keycode, InputEvent&> mInputEvents;
    
public:
    InputManager() = default;
    ~InputManager();
    InputManager& operator=(const InputManager&) = delete;

    static InputManager& Instance();
    void HandleInputs(SDL_Event& event);
    void BindTo(SDL_Keycode keyCode, IInputListener* listener);    
};
