/**
 * @file PhysicEngine.h
 * @brief Declaration of the PhysicEngine class, which manages physics simulation, rigidbodies, and constraints.
 */

#pragma once
#include <deque>

#include "Constraint.h"

/**
 * @class PhysicEngine
 * @brief Singleton class that manages all physics simulation, rigidbody components, and constraints.
 */
class PhysicEngine
{
private:
    /**
     * @brief Private constructor for singleton pattern.
     */
    PhysicEngine();

    /**
     * @brief Destructor, cleans up constraints.
     */
    ~PhysicEngine();

    /**
     * @brief List of all registered rigidbody components.
     */
    std::deque<RigidbodyComponent*> mRigidbodyComponents;

    /**
     * @brief List of all registered constraints.
     */
    std::deque<Constraint*> mConstraints;

    /**
     * @brief List of global forces to apply.
     */
    std::deque<Vec3> mForces;

    /**
     * @brief List of global torques to apply.
     */
    std::deque<Vec3> mTorques;

public:
    /**
     * @brief Gets the singleton instance of the PhysicEngine.
     * @return Reference to the PhysicEngine instance.
     */
    static PhysicEngine& GetInstance()
    {
        static PhysicEngine instance;
        return instance;
    }

    /**
     * @brief Deleted copy constructor.
     */
    PhysicEngine(const PhysicEngine&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    PhysicEngine& operator=(const PhysicEngine&) = delete;

    /**
     * @brief Updates the physics simulation for all rigidbodies and constraints.
     */
    void Update();

    /**
     * @brief Adds a rigidbody to the simulation.
     * @param rigidbody Pointer to the RigidbodyComponent to add.
     */
    void AddRigidbody(RigidbodyComponent* rigidbody);

    /**
     * @brief Removes a rigidbody from the simulation.
     * @param rigidbody Pointer to the RigidbodyComponent to remove.
     */
    void RemoveRigidbody(RigidbodyComponent* rigidbody);

    /**
     * @brief Gets the list of constraints.
     * @return Reference to the deque of Constraint pointers.
     */
    std::deque<Constraint*>& GetConstraints()
    {
        return mConstraints;
    }

    /**
     * @brief Gets the list of rigidbodies.
     * @return Reference to the deque of RigidbodyComponent pointers.
     */
    std::deque<RigidbodyComponent*>& GetRigidbodies()
    {
        return mRigidbodyComponents;
    }
};
