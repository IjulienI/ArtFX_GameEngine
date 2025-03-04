#include "SpriteComponent.h"

#include "../Engine/Core/Class/Actor/Actor.h"
#include "../Engine/Core/Class/Scene/Scene.h"
#include "Math/Rectangle.h"


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

void SpriteComponent::Draw(Renderer& pRenderer)
{
    Vec2 origin {mTexWidth/2.0f, mTexHeight/2.0f};
    pRenderer.DrawSprite(*mOwner, mTexture, Rectangle(), origin, Flip::NONE);
}

void SpriteComponent::SetFlipX(bool status)
{
    mOrientation = status ? Flip::HORIZONTAL : Flip::NONE;
}
