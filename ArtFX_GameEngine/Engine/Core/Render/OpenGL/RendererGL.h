#pragma once

#include "Core/Render/Interface/IRenderer.h"
#include "VertexArray.h"
#include <vector>

#include "Core/Render/Shader/ShaderProgram.h"

class SpriteComponent;

class RendererGL : public IRenderer
{
private:
    Window* mWindow;
    VertexArray* mVao;
    SDL_GLContext mContext;
    std::vector<SpriteComponent*> mSprites;
    ShaderProgram* mShaderProgram;
public:
    RendererGL();
    virtual ~RendererGL() override;
    RendererGL(const RendererGL&) = delete;
    RendererGL& operator =(const RendererGL&) = delete;

    bool Initialize(Window& rWindow) override;
    void BeginDraw() override;
    void Draw() override;
    void DrawSprites() override;
    void EndDraw() override;

    void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) override;
    void AddSprite(SpriteComponent* sprite) override;
    void RemoveSprite(SpriteComponent* sprite) override;
    void Close() override;
    RendererType GetType() override;
    
    
};
