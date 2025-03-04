#pragma once
#include "Core/Class/Component/Component.h"
#include "Core/Render/Texture.h"


enum class Flip;

class SpriteComponent : public Component
{
protected:
    Texture mTexture;
    int mDrawOrder;
    int mTexWidth, mTexHeight;
    Flip mOrientation;
    
public:
    SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100);
    virtual ~SpriteComponent();
    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent& operator= (const SpriteComponent&) = delete;

    virtual void SetTexture(const Texture& pTexture);
    virtual void Draw(Renderer& pRenderer);
    void SetFlipX(bool status);

public:
    int GetDrawOrder() const {return mDrawOrder;}
    int GetTexWidth() const {return mTexWidth;}
    int GetTexHeight() const {return mTexHeight;}
};
