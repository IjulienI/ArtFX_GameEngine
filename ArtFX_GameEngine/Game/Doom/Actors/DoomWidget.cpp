#include "DoomWidget.h"

#include "Core/Render/Asset.h"
#include "Core/Render/Component/SpriteComponent.h"

DoomWidget::DoomWidget() : Actor()
{
    
}

void DoomWidget::Start()
{
    Actor::Start();
    sprite = new SpriteComponent(this, Asset::GetTexture("BaseTexture"));
    SetScale(Vec3(1, 1, 1));
    SetLocation(Vec3(0, 0, 1000));
}

void DoomWidget::Update()
{
    Actor::Update();
}

void DoomWidget::Destroy()
{
    Actor::Destroy();
}
