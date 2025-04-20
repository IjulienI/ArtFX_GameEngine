#pragma once

#include "Core/Render/Interface/IRenderer.h"
#include "VertexArray.h"
#include <vector>

class SpriteComponent;

class RendererGL : public IRenderer
{
private:
    Window* mWindow;
    VertexArray* mSpriteVAO;
    SDL_GLContext mContext;
    ShaderProgram* mSpriteShaderProgram;
    Shader mSpriteVertexShader, mSpriteFragmentShader;
    Matrix4Row mSpriteViewProj;
    Matrix4Row mView;
    Matrix4Row mProj;
public:
    RendererGL();
    virtual ~RendererGL() override;
    RendererGL(const RendererGL&) = delete;
    RendererGL& operator =(const RendererGL&) = delete;

    bool Initialize(Window& rWindow) override;
    void BeginDraw() override;
    void Draw() override;
    void DrawSprites() override;
    void DrawMeshes() override;
    void EndDraw() override;
    void Close() override;

    void SetSpriteShaderProgram(ShaderProgram* shaderProgram);

    void DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation) override;
    void AddSprite(SpriteComponent* sprite) override;
    void RemoveSprite(SpriteComponent* sprite) override;

    void ShowWireframe(bool status);

    void AddMesh(MeshComponent* mesh) override;
    void RemoveMesh(MeshComponent* mesh) override;

    void SetViewMatrix(Matrix4Row matrix) override;

    RendererType GetType() override;      
};

