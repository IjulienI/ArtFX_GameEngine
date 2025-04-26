#pragma once
#include "Core/Class/Actor/Actor.h"

class Pin;

class PinManager : public Actor
{
private:
    std::vector<Pin*> mPins;
    std::vector<Vec3> mPinsBasePosition;
    bool mValidPin[10];
    
public:
    PinManager();
    ~PinManager() override = default;
    
    void Start() override;
    void Update() override;
    void Destroy() override;

    void SetPinPhysisc(bool pEnable) const;

    int CheckValidPin() const;
    void ResetNoHittendPins() const;
    void ResetGame() const;
    
};
