/**
 * @file RendererSdl.h
 * @brief Declaration of the RendererSdl class, which provides SDL-based rendering functionality.
 */

#pragma once

#include <vector>
#include "Interface/IRenderer.h"

class SpriteComponent;

/**
 * @class RendererSdl
 * @brief SDL-based renderer for handling sprites and rectangles.
 */
class RendererSdl : public IRenderer
{
private:
    /**
     * @brief Pointer to the SDL renderer.
     */
    SDL_Renderer* mSdlRenderer;

    /**
     * @brief List of sprite components to render.
     */
    std::vector<SpriteComponent*> mSprites;

public:
    /**
     * @brief Constructs a RendererSdl object.
     */
    RendererSdl();

    /**
     * @brief Deleted copy constructor.
     */
    RendererSdl(const RendererSdl&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    RendererSdl& operator= (const RendererSdl&) = delete;

    /**
     * @brief Destructor for RendererSdl.
     */
    virtual ~RendererSdl() override = default;

    /**
     * @brief Initializes the SDL renderer with the given window.
     * @param rWindow Reference to the window object.
     * @return True if initialization succeeded, false otherwise.
     */
    bool Initialize(Window& rWindow) override;

    /**
     * @brief Begins the drawing process by clearing the screen.
     */
    void BeginDraw() override;

    /**
     * @brief Draws all registered objects.
     */
    void Draw() override;

    /**
     * @brief Ends the drawing process and presents the rendered frame.
     */
    void EndDraw() override;

    /**
     * @brief Closes the renderer and releases resources.
     */
    void Close() override;

    /**
     * @brief Draws a rectangle with the specified color.
     * @param rRect Rectangle to draw.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param a Alpha color component (default is 255).
     */
    void DrawRect(Rectangle& rRect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    /**
     * @brief Draws a sprite for a given actor using the specified texture and transformation.
     * @param actor Reference to the actor.
     * @param tex Reference to the texture.
     * @param rect Source rectangle for the texture.
     * @param pos Position to draw the sprite.
     * @param orientation Flip orientation for the sprite.
     */
    void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) override;

    /**
     * @brief Draws all registered sprite components.
     */
    void DrawSprites() override;

    /**
     * @brief Adds a sprite component to the renderer.
     * @param component Pointer to the sprite component.
     */
    void AddSprite(SpriteComponent* component) override;

    /**
     * @brief Removes a sprite component from the renderer.
     * @param component Pointer to the sprite component.
     */
    void RemoveSprite(SpriteComponent* component) override;

    /**
     * @brief Gets the type of the renderer.
     * @return RendererType enum value.
     */
    RendererType GetType() override;

    /**
     * @brief Converts the renderer to an SDL_Renderer pointer.
     * @return Pointer to the SDL_Renderer.
     */
    SDL_Renderer* ToSdlRenderer();
};
