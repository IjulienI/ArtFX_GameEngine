#include "PinManager.h"

#include "Bowling/BowlingConstants.h"
#include "Bowling/Actors/Pin.h"
#include "Core/Physic/Component/RigidbodyComponent.h"

PinManager::PinManager() : Actor()
{
    mClassName = "PinManager";
    mName = "PinManager_01";
    PinManager::Start();
}

void PinManager::Start()
{
    Actor::Start();
    
    // Pin layout
    mPins.reserve(10);
    mPinsBasePosition.reserve(10);

    int pinIndex = 10;
    for (int i = 0; i < 4; i++)
    {
        int pinInJ = 4 - i;
        float start = -PIN_SPACING * 0.5f * (pinInJ - 1);
        
        for (int j = 0; j < pinInJ; j++)
        {            
            Pin* pin = new Pin();
            mScene->AddActor(pin);
            
            pin->SetName("Pin_" + std::to_string(pinIndex));
            pin->SetLocation(Vec3((start + j * PIN_SPACING) - PIN_POS_X, (i * PIN_ROW_HEIGHT) + 0.3f, 0.4f));
            
            mPins.push_back(pin);
            mPinsBasePosition.push_back(pin->GetLocation());
            pinIndex--;
        }
    }    
}

void PinManager::Update()
{
    Actor::Update();
}

void PinManager::Destroy()
{
    Actor::Destroy();
}

void PinManager::SetPinPhysisc(bool pEnable) const
{
    float mass = pEnable? PIN_MASS : 0.0f;
    for (Pin* pin : mPins)
    {
        pin->GetComponent<RigidbodyComponent>()->SetMass(mass);
    }
}

int PinManager::CheckValidPin() const
{
    int result = 0;
    for (int i = 0; i < mPins.size(); i++)
    {
        if (!mPins[i]->GetLocation().NearEquals(mPinsBasePosition[i], 0.5f))
        {
            mPins[i]->SetHitted(true);
            result++;
        }
    }
    return result;
}

void PinManager::ResetNoHittendPins() const
{
    for (int i = 0; i < mPins.size(); i++)
    {
        if (!mPins[i]->GetHitted())
        {
            mPins[i]->GetComponent<RigidbodyComponent>()->ClearAll();
            mPins[i]->SetLocation(mPinsBasePosition[i]);
            mPins[i]->SetRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
            mPins[i]->Rotate(Vec3(90.0f, 0.0f, 0.0f));
        }
        else
        {
            mPins[i]->GetComponent<RigidbodyComponent>()->ClearAll();
            mPins[i]->SetLocation(Vec3());
        }
    }
}

void PinManager::ResetGame() const
{
    for (int i = 0; i < mPins.size(); i++)
    {
        mPins[i]->GetComponent<RigidbodyComponent>()->ClearAll();
        mPins[i]->SetLocation(mPinsBasePosition[i]);
        mPins[i]->SetRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
        mPins[i]->Rotate(Vec3(90.0f, 0.0f, 0.0f));
        mPins[i]->SetHitted(false);
    }
}
