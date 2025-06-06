/**
 * @file Window.cpp
 * @brief Implementation of the Window class, which manages the creation and handling of an SDL window.
 */

#include "Window.h"
#include "../../Debug/Log.h"

/**
 * @brief Initializes the static Dimensions variable with default values.
 */
Vec2 Window::Dimensions = { 1920.0f, 1080.0f };

/**
 * @brief Constructs a Window object with the specified dimensions and title.
 * @param pWitdh Width of the window.
 * @param pHeight Height of the window.
 * @param pTitle Title of the window.
 */
Window::Window(int pWitdh, int pHeight, std::string pTitle)
{
    mSdlWindow = nullptr;
    mTitle = pTitle;
    Dimensions = {static_cast<float>(pWitdh), static_cast<float>(pHeight)};
}

/**
 * @brief Copy constructor for Window.
 */
Window::Window(const Window&)
{
}

/**
 * @brief Opens the window and initializes SDL.
 * @return True if the window was successfully opened, false otherwise.
 */
bool Window::Open()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Log::Error(LogType::Video, "Unable to initialize video");
        return false;
    }
    mSdlWindow = SDL_CreateWindow(mTitle.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    static_cast<int>(Dimensions.x), static_cast<int>(Dimensions.y), SDL_WINDOW_OPENGL);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    if(!mSdlWindow)
    {
        Log::Error(LogType::System, "Failed to create window");
        return false;
    }
    return true;
}

/**
 * @brief Closes the window and releases resources.
 */
void Window::Close()
{
    SDL_DestroyWindow(mSdlWindow);
}

/**
 * @brief Updates the window (placeholder for future functionality).
 */
void Window::Update()
{
}
