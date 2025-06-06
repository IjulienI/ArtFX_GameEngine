/**
 * @file RendererGL.h
 * @brief Declaration of the RendererGL class, which provides OpenGL-based rendering functionality.
 */

#pragma once

#include "Core/Render/Interface/IRenderer.h"
#include "VertexArray.h"
#include <vector>

class SpriteComponent;

/**
 * @class RendererGL
 * @brief OpenGL-based renderer for handling sprites, meshes, and collision shapes.
 */
class RendererGL : public IRenderer
{
private:
    /**
     * @brief Pointer to the window used for rendering.
     */
    Window* mWindow;

    /**
     * @brief Vertex array object for rendering sprites.
     */
    VertexArray* mSpriteVAO;

    /**
     * @brief OpenGL context for rendering.
     */
    SDL_GLContext mContext;

    /**
     * @brief Shader program used for rendering sprites.
     */
    ShaderProgram mSpriteShaderProgram;

    /**
     * @brief Vertex and fragment shaders for sprite rendering.
     */
    Shader mSpriteVertexShader, mSpriteFragmentShader;

    /**
     * @brief View-projection matrix for sprite rendering.
     */
    Matrix4Row mSpriteViewProj;

    /**
     * @brief View matrix for rendering.
     */
    Matrix4Row mView;

    /**
     * @brief Projection matrix for rendering.
     */
    Matrix4Row mProj;

public:
    /**
     * @brief Constructs a RendererGL object and initializes rendering matrices.
     */
    RendererGL();

    /**
     * @brief Destructor for RendererGL.
     */
    virtual ~RendererGL() override;

    /**
     * @brief Deleted copy constructor.
     */
    RendererGL(const RendererGL&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    RendererGL& operator =(const RendererGL&) = delete;

    /**
     * @brief Initializes the OpenGL renderer with the given window.
     * @param rWindow Reference to the window object.
     * @return True if initialization succeeded, false otherwise.
     */
    bool Initialize(Window& rWindow) override;

    /**
     * @brief Begins the drawing process by clearing the screen.
     */
    void BeginDraw() override;

    /**
     * @brief Draws all registered objects based on the current draw type.
     */
    void Draw() override;

    /**
     * @brief Draws all registered sprite components.
     */
    void DrawSprites() override;

    /**
     * @brief Draws all registered mesh components.
     */
    void DrawMeshes() override;

    /**
     * @brief Draws all registered collision components.
     */
    void DrawCollisions() override;

    /**
     * @brief Ends the drawing process and swaps the window buffers.
     */
    void EndDraw() override;

    /**
     * @brief Closes the renderer and releases resources.
     */
    void Close() override;

    /**
     * @brief Sets the shader program for rendering sprites.
     * @param shaderProgram Pointer to the shader program.
     */
    void SetSpriteShaderProgram(ShaderProgram* shaderProgram);

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
     * @brief Adds a sprite component to the renderer.
     * @param sprite Pointer to the sprite component.
     */
    void AddSprite(SpriteComponent* sprite) override;

    /**
     * @brief Removes a sprite component from the renderer.
     * @param sprite Pointer to the sprite component.
     */
    void RemoveSprite(SpriteComponent* sprite) override;

    /**
     * @brief Toggles wireframe rendering mode.
     * @param status True to enable wireframe mode, false to disable.
     */
    void ShowWireframe(bool status);

    /**
     * @brief Adds a mesh component to the renderer.
     * @param mesh Pointer to the mesh component.
     */
    void AddMesh(MeshComponent* mesh) override;

    /**
     * @brief Removes a mesh component from the renderer.
     * @param mesh Pointer to the mesh component.
     */
    void RemoveMesh(MeshComponent* mesh) override;

    /**
     * @brief Adds a collision component to the renderer.
     * @param collision Pointer to the collision component.
     */
    void AddCollision(BaseCollisionComponent* collision) override;

    /**
     * @brief Removes a collision component from the renderer.
     * @param collision Pointer to the collision component.
     */
    void RemoveCollision(BaseCollisionComponent* collision) override;

    /**
     * @brief Sets the view matrix for rendering.
     * @param matrix The view matrix.
     */
    void SetViewMatrix(Matrix4Row matrix) override;

    /**
     * @brief Sets the draw type for rendering.
     * @param type The draw type.
     */
    void SetDawType(DrawType type) override;

    /**
     * @brief Gets the type of the renderer.
     * @return RendererType enum value.
     */
    RendererType GetType() override;
};
