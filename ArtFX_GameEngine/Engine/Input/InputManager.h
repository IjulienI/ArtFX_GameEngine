#pragma once

#include <map>
#include "InputEvent.h"

class InputManager
{
    std::map<SDL_Scancode, InputEvent*> mInputEvents;

    SDL_Scancode keys [SDL_NUM_SCANCODES];
    
public:
    InputManager() = default;
    ~InputManager();
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    static InputManager& Instance();
    void HandleInputs(SDL_Event& event);
    
    void BindTo(SDL_Scancode keyCode, IInputListener* listener);
};
