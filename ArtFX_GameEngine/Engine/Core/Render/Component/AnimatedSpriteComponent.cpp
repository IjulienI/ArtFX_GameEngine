#include "AnimatedSpriteComponent.h"

#include "Math/Time.h"


AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* actor, const std::vector<Texture*>& textures, int drawOrder) :
SpriteComponent(actor, *textures[0], drawOrder), mCurrentFrame(0.0f), mAnimFps(0.0f)
{
    SetAnimationTextures(textures);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
}

float AnimatedSpriteComponent::GetAnimationFps()
{
    return mAnimFps;
}

void AnimatedSpriteComponent::SetAnimationTextures(const std::vector<Texture*>& textures)
{
    mAnimationTextures = textures;
    if(!mAnimationTextures.empty())
    {
        SetTexture(*mAnimationTextures[0]);
    }
}

void AnimatedSpriteComponent::SetAnimationFps(float fps)
{
    mAnimFps = fps;
}

void AnimatedSpriteComponent::Update()
{
    SpriteComponent::Update();
    if(mAnimationTextures.empty()) return;
    
    mCurrentFrame += mAnimFps * Time::deltaTime;
    while(mCurrentFrame >= static_cast<float>(mAnimationTextures.size()))
    {
        mCurrentFrame -= static_cast<float>(mAnimationTextures.size());
    }
    SetTexture(*mAnimationTextures[static_cast<int>(mCurrentFrame)]);
}
