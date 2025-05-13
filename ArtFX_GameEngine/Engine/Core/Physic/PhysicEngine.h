#pragma once
#include <deque>

#include "Constraint.h"

class PhysicEngine
{
    
private:    
    PhysicEngine();
    ~PhysicEngine();
    
    std::deque<RigidbodyComponent*> mRigidbodyComponents;
    std::deque<Constraint*> mConstraints;
    std::deque<Vec3> mForces;
    std::deque<Vec3> mTorques;
    
public:
    static PhysicEngine& GetInstance()
    {
        static PhysicEngine instance;
        return instance;
    }

    PhysicEngine(const PhysicEngine&) = delete;
    PhysicEngine& operator=(const PhysicEngine&) = delete;

    void Update();

    void AddRigidbody(RigidbodyComponent* rigidbody);
    void RemoveRigidbody(RigidbodyComponent* rigidbody);
    
    std::deque<Constraint*>& GetConstraints()
    {
        return mConstraints;
    }

    std::deque<RigidbodyComponent*>& GetRigidbodies()
    {
        return mRigidbodyComponents;
    }
    
};
