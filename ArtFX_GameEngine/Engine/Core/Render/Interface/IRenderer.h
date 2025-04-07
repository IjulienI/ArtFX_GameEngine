#pragma once

#include "../Engine/Core/Render/Window.h"
#include "Core/Render/Shader/ShaderProgram.h"
#include "Math/Rectangle.h"

class SpriteComponent;
class Actor;
class Texture;

class IRenderer
{
public:
    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };

    enum class RendererType
    {
        SDL,
        OPENGL
    };
    
    virtual ~IRenderer() = default;

    virtual bool Initialize(Window& rWindow) = 0;
    virtual void BeginDraw() = 0;
    virtual void Draw() = 0;
    virtual void DrawSprites() = 0;
    virtual void EndDraw() = 0;
    virtual void Close() = 0;
    virtual RendererType GetType() = 0;

    virtual void AddSprite(SpriteComponent* sprite) = 0;
    virtual void RemoveSprite(SpriteComponent* sprite) = 0;
    virtual void SetShaderProgram(ShaderProgram* shaderProgram) = 0;

    virtual void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) = 0;
};