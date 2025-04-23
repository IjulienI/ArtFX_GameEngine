#pragma once
#include <vector>

#include "Core/Class/Component/Component.h"
#include "Math/MatMN.h"

class BaseCollisionComponent;

class RigidbodyComponent : public Component
{
private:
    bool mStatic;
    
    Vec3 mVelocity;
    Vec3 mAcceleration;

    Vec3 mAngularVelocity;
    Vec3 mAngularAcceleration;

    Vec3 mSumForces;
    Vec3 mSumTorques;

    float mMass;
    float mInverseMass;

    float mRestitution;

    float mFriction;

    MatMN mMomentOfInertia{3,3};
    MatMN mInverseMomentOfInertia{3,3};

    void CalcMomentOfInertia();

    BaseCollisionComponent* mCollisionComponent;
    
public:
    RigidbodyComponent(Actor* pOwner);
    void OnStart() override;
    void Update() override;
    void OnEnd() override;

    bool IsStatic() const;

    //Getter Setters
    void SetMass(float pMass);
    float GetMass() const
    {
        return mMass;
    }

    void AddForce(const Vec3& pForce);
    void AddTorque(const Vec3& pTorque);
    
    void ClearForces();
    void ClearTorques();

    float GetInverseMass() const
    {
        return mInverseMass;
    }
    Vec3 GetVelocity() const
    {
        return mVelocity;
    }
    Vec3 GetAngularVelocity() const
    {
        return mAngularVelocity;
    }
    MatMN GetMomentOfInertia() const
    {
        return mMomentOfInertia;
    }
    MatMN GetInverseMomentOfInertia() const
    {
        return mInverseMomentOfInertia;
    }
    float GetRestitution() const
    {
        return mRestitution;
    }
    float GetFriction() const
    {
        return mFriction;
    }

    Vec3 GetLocation() const;

    void SetCollisionComponent(BaseCollisionComponent* pCollisionComponent);
    BaseCollisionComponent* GetCollisionComponent() const
    {
        return mCollisionComponent;
    }

    std::vector<Vec3> GetLocalAxes() const;

    //Logic
    void ApplyImpulseAngular(const Vec3& pImpulse);
    void ApplyImpulseLinear(const Vec3& pImpulse);
    void ApplyImpulseAtPoint(const Vec3& pImpulse, const Vec3& pPoint);

    void IntegrateForces();

    void IntegrateVelocity();

    void ApplyImpulse(const Vec3& pImpulse);

    Vec3 WorldSpaceToLocalSpace(const Vec3& pPoint) const;
    Vec3 LocalSpaceToWorldSpace(const Vec3& pPoint) const;
    
};
