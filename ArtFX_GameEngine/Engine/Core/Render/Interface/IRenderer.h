/**
 * @file IRenderer.h
 * @brief Declaration of the IRenderer interface for rendering systems.
 */

#pragma once

#include "../Engine/Core/Render/Window.h"
#include "Core/Render/OpenGL/DrawType.h"
#include "Core/Render/Shader/ShaderProgram.h"
#include "Math/Rectangle.h"

class BaseCollisionComponent;
class MeshComponent;
class SpriteComponent;
class Actor;
class Texture;

/**
 * @class IRenderer
 * @brief Interface for rendering systems (SDL, OpenGL, etc.).
 */
class IRenderer
{
protected:
    /**
     * @brief List of sprite components to render.
     */
    std::vector<SpriteComponent*> mSprites;
    /**
     * @brief List of mesh components to render.
     */
    std::vector<MeshComponent*> mMeshes;
    /**
     * @brief List of collision components to render.
     */
    std::vector<BaseCollisionComponent*> mCollisions;

    /**
     * @brief Current draw type (wireframe, solid, etc.).
     */
    DrawType mDrawType;
public:
    /**
     * @enum Flip
     * @brief Sprite flipping options.
     */
    enum class Flip
    {
        None = SDL_FLIP_NONE,        /**< No flip. */
        Horizontal = SDL_FLIP_HORIZONTAL, /**< Flip horizontally. */
        Vertical = SDL_FLIP_VERTICAL      /**< Flip vertically. */
    };

    /**
     * @enum RendererType
     * @brief Supported renderer types.
     */
    enum class RendererType
    {
        SDL,    /**< SDL renderer. */
        OPENGL  /**< OpenGL renderer. */
    };
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~IRenderer() = default;

    /**
     * @brief Initializes the renderer with a window.
     * @param rWindow Reference to the window.
     * @return True if initialization succeeded.
     */
    virtual bool Initialize(Window& rWindow) = 0;

    /**
     * @brief Begins the drawing process.
     */
    virtual void BeginDraw() = 0;

    /**
     * @brief Draws all registered objects.
     */
    virtual void Draw() = 0;

    /**
     * @brief Draws all registered sprites.
     */
    virtual void DrawSprites() = 0;

    /**
     * @brief Draws all registered meshes.
     */
    virtual void DrawMeshes() = 0;

    /**
     * @brief Draws all registered collision shapes.
     */
    virtual void DrawCollisions() = 0;

    /**
     * @brief Ends the drawing process.
     */
    virtual void EndDraw() = 0;

    /**
     * @brief Closes the renderer and releases resources.
     */
    virtual void Close() = 0;

    /**
     * @brief Gets the type of the renderer.
     * @return RendererType enum value.
     */
    virtual RendererType GetType() = 0;

    /**
     * @brief Draws a sprite for a given actor.
     * @param actor The actor to draw.
     * @param tex The texture to use.
     * @param rect The source rectangle.
     * @param pos The position to draw at.
     * @param orientation The flip orientation.
     */
    virtual void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) = 0;

    // Getter Setters

    /**
     * @brief Adds a sprite component to the renderer.
     * @param sprite Pointer to the sprite component.
     */
    virtual void AddSprite(SpriteComponent* sprite) = 0;

    /**
     * @brief Removes a sprite component from the renderer.
     * @param sprite Pointer to the sprite component.
     */
    virtual void RemoveSprite(SpriteComponent* sprite) = 0;

    /**
     * @brief Adds a collision component to the renderer.
     * @param collision Pointer to the collision component.
     */
    virtual void AddCollision(BaseCollisionComponent* collision) = 0;

    /**
     * @brief Removes a collision component from the renderer.
     * @param collision Pointer to the collision component.
     */
    virtual void RemoveCollision(BaseCollisionComponent* collision) = 0;

    /**
     * @brief Adds a mesh component to the renderer.
     * @param mesh Pointer to the mesh component.
     */
    virtual void AddMesh(MeshComponent* mesh) = 0;

    /**
     * @brief Removes a mesh component from the renderer.
     * @param mesh Pointer to the mesh component.
     */
    virtual void RemoveMesh(MeshComponent* mesh) = 0;

    /**
     * @brief Sets the view matrix for rendering.
     * @param matrix The view matrix.
     */
    virtual void SetViewMatrix(Matrix4Row matrix) = 0;

    /**
     * @brief Sets the draw type (wireframe, solid, etc.).
     * @param type The draw type.
     */
    virtual void SetDawType(DrawType type) = 0;
};
