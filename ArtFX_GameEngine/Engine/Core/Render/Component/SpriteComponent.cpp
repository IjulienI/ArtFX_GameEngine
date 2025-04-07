#include "SpriteComponent.h"

#include "../Engine/Core/Class/Actor/Actor.h"
#include "../Engine/Core/Class/Scene/Scene.h"


SpriteComponent::SpriteComponent(Actor* owner, Texture& texture, int drawOrder):
Component(owner),
mTexture(texture),
mDrawOrder(drawOrder),
mTexWidth(texture.GetWidht()),
mTexHeight(texture.GetHeight())
{
    mOwner->GetScene()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetScene()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
    mTexture = pTexture;
    mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(IRenderer& pRenderer)
{
    Vec2 origin {static_cast<float>(mTexWidth)/2.0f, static_cast<float>(mTexHeight)/2.0f};
    pRenderer.DrawSprite(*mOwner, mTexture, Rectangle(), origin, mOrientation);
}

void SpriteComponent::SetFlipX(bool status)
{
    mOrientation = status ? IRenderer::Flip::Horizontal : IRenderer::Flip::None;
}
