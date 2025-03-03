#pragma once

#include <vector>
#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
private:
    std::vector<Texture*> mAnimationTextures;
    float mCurrentFrame;
    float mAnimFps;

public:
    AnimatedSpriteComponent(Actor* actor, const std::vector<Texture*>& textures, int drawOrder = 100);
    virtual ~AnimatedSpriteComponent() override;
    AnimatedSpriteComponent() = delete;
    AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
    AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

    float GetAnimationFps();
    void SetAnimationTextures(const std::vector<Texture*>& textures);
    void SetAnimationFps(float fps);

    void Update() override;  
};
