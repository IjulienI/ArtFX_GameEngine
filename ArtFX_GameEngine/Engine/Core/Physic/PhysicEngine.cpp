#include <vector>
#include <Core/Physic/PhysicEngine.h>

#include "CollisionDetection.h"
#include "Contact.h"
#include "PhysicConstants.h"

PhysicEngine::PhysicEngine() =default;

PhysicEngine::~PhysicEngine()
{
    for (Constraint* constraint : mConstraints)
    {
        delete constraint;
    }
}

void PhysicEngine::Update()
{
    if (mRigidbodyComponents.empty()) return;
    
    std::vector<PenetrationConstraint> penetrations;

    for (RigidbodyComponent* rigidbody : mRigidbodyComponents)
    {
        Vec3 weight = Vec3(0.0f, 0.0f, rigidbody->GetMass() * GRAVITY * PIXELS_PER_METER);
        rigidbody->AddForce(weight);

        for (Vec3 force : mForces)
        {
            rigidbody->AddForce(force);
        }
        for (Vec3 torque : mTorques)
        {
            rigidbody->AddTorque(torque);
        }
    }
    for (RigidbodyComponent* rigidbody : mRigidbodyComponents)
    {
        rigidbody->IntegrateForces();
    }

    for (int i = 0; i <= mRigidbodyComponents.size() - 1; i++) {
        for (int j = i + 1; j < mRigidbodyComponents.size(); j++) {
            RigidbodyComponent* a = mRigidbodyComponents[i];
            RigidbodyComponent* b = mRigidbodyComponents[j];

            std::vector<Contact> contacts;
            if (CollisionDetection::IsColliding(a, b, contacts)) {
                for (auto contact : contacts) {
                    PenetrationConstraint penetretion(contact.a, contact.b, contact.start, contact.end, contact.normal);
                    penetrations.push_back(penetretion);
                }
            }
        }
    }

    for (auto& constraint : mConstraints) {
        constraint->PreSolve();
    }

    for (auto& constraint : penetrations) {
        constraint.PreSolve();
    }
    
    for (auto& constraint : mConstraints) {
        constraint->Solve();
    }
    for (auto& constraint : penetrations) {
        constraint.Solve();
    }

    for (auto& constraint : mConstraints) {
        constraint->PostSolve();
    }

    for (auto& constraint : penetrations) {
        constraint.PostSolve();
    }

    for (auto& rigidbody : mRigidbodyComponents) {
        rigidbody->IntegrateVelocity();
    }
}

void PhysicEngine::AddRigidbody(RigidbodyComponent* rigidbody)
{
    mRigidbodyComponents.push_back(rigidbody);
}

void PhysicEngine::RemoveRigidbody(RigidbodyComponent* rigidbody)
{
}

