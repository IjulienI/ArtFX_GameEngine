/**
 * @file Window.h
 * @brief Declaration of the Window class, which manages the creation and handling of an SDL window.
 */

#pragma once
#include <SDL.h>
#include "../../Math/Vec2.h"
#include <string>

/**
 * @class Window
 * @brief Represents an SDL window and provides methods for managing its lifecycle.
 */
class Window
{
private:
    /**
     * @brief Title of the window.
     */
    std::string mTitle;

    /**
     * @brief Pointer to the SDL window object.
     */
    SDL_Window* mSdlWindow = nullptr;

public:
    /**
     * @brief Dimensions of the window (width and height).
     */
    static Vec2 Dimensions;

    /**
     * @brief Constructs a Window object with the specified dimensions and title.
     * @param pWitdh Width of the window.
     * @param pHeight Height of the window.
     * @param pTitle Title of the window.
     */
    Window(int pWitdh, int pHeight, std::string pTitle);

    /**
     * @brief Copy constructor for Window.
     */
    Window(const Window&);

    /**
     * @brief Deleted assignment operator.
     */
    Window& operator=(const Window&) = delete;

    /**
     * @brief Gets the dimensions of the window.
     * @return Dimensions as a Vec2 object.
     */
    Vec2 GetDimensions() const { return Dimensions; }

    /**
     * @brief Gets the SDL window object.
     * @return Pointer to the SDL window object.
     */
    SDL_Window* GetSldWindow() const { return mSdlWindow; }

    /**
     * @brief Opens the window and initializes SDL.
     * @return True if the window was successfully opened, false otherwise.
     */
    bool Open();

    /**
     * @brief Closes the window and releases resources.
     */
    void Close();

    /**
     * @brief Updates the window (placeholder for future functionality).
     */
    void Update();
};
