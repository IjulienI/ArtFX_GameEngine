#pragma once
#include "Core/Class/Actor/Actor.h"

class Pin : public Actor
{
private:
    bool mHitted;
    
public:
    Pin();
    ~Pin() override = default;
    
    void Start() override;
    void Update() override;
    void Destroy() override;

    bool GetHitted()
    {
        return mHitted;
    }
    void SetHitted(bool pHitted);
};
