#pragma once

#include "Core/Class/Component/Component.h"
#include "Core/Render/Texture.h"
#include "Core/Render/Interface/IRenderer.h"

class SpriteComponent : public Component
{
protected:
    Texture mTexture;
    int mDrawOrder;
    int mTexWidth, mTexHeight;
    IRenderer::Flip mOrientation;
    
public:
    SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100);
    virtual ~SpriteComponent() override;
    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent& operator= (const SpriteComponent&) = delete;

    virtual void SetTexture(const Texture& pTexture);
    virtual void Draw(RendererSdl& pRenderer);
    void SetFlipX(bool status);

public:
    int GetDrawOrder() const {return mDrawOrder;}
    int GetTexWidth() const {return mTexWidth;}
    int GetTexHeight() const {return mTexHeight;}
};
