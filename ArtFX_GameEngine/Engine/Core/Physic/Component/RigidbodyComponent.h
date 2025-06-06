/**
 * @file RigidbodyComponent.h
 * @brief Declaration of the RigidbodyComponent class, which handles physics simulation for an Actor.
 */

#pragma once
#include <vector>
#include "Core/Class/Component/Component.h"
#include "Math/Mat3.h"
#include "Math/MatMN.h"

class BaseCollisionComponent;

/**
 * @class RigidbodyComponent
 * @brief Component that adds physics simulation (rigid body dynamics) to an Actor.
 */
class RigidbodyComponent : public Component
{
private:
    /**
     * @brief Whether the rigidbody is static (immovable).
     */
    bool mStatic;
    
    /**
     * @brief Linear velocity of the rigidbody.
     */
    Vec3 mVelocity;

    /**
     * @brief Linear acceleration of the rigidbody.
     */
    Vec3 mAcceleration;

    /**
     * @brief Angular velocity of the rigidbody.
     */
    Vec3 mAngularVelocity;

    /**
     * @brief Angular acceleration of the rigidbody.
     */
    Vec3 mAngularAcceleration;

    /**
     * @brief Sum of all forces applied to the rigidbody.
     */
    Vec3 mSumForces;

    /**
     * @brief Sum of all torques applied to the rigidbody.
     */
    Vec3 mSumTorques;

    /**
     * @brief Mass of the rigidbody.
     */
    float mMass;

    /**
     * @brief Inverse mass (1/mass) for calculations.
     */
    float mInverseMass;

    /**
     * @brief Gravity scale factor.
     */
    float mGravityScale = 1.0f; 

    /**
     * @brief Restitution (bounciness) coefficient.
     */
    float mRestitution;

    /**
     * @brief Friction coefficient.
     */
    float mFriction;

    /**
     * @brief Angular damping factor.
     */
    float mAngularDamping;

    /**
     * @brief Linear damping factor.
     */
    float mLinearDamping;

    /**
     * @brief Moment of inertia tensor.
     */
    Mat3 mMomentOfInertia;

    /**
     * @brief Inverse moment of inertia tensor.
     */
    Mat3 mInverseMomentOfInertia;

    /**
     * @brief Whether rotation is locked.
     */
    bool mLockRotation = false;

    /**
     * @brief Calculates the moment of inertia tensor.
     */
    void CalcMomentOfInertia();

    /**
     * @brief Pointer to the associated collision component.
     */
    BaseCollisionComponent* mCollisionComponent;

    Vec3 mVelocityMultiplier = Vec3::one;
    
public:
    /**
     * @brief Constructs a RigidbodyComponent.
     * @param pOwner Pointer to the owning Actor.
     */
    RigidbodyComponent(Actor* pOwner);

    /**
     * @brief Called when the component is started.
     */
    void OnStart() override;

    /**
     * @brief Updates the rigidbody component every frame.
     */
    void Update() override;

    /**
     * @brief Called when the component is about to be destroyed or removed.
     */
    void OnEnd() override;

    /**
     * @brief Checks if the rigidbody is static (immovable).
     * @return True if static, false otherwise.
     */
    bool IsStatic() const;

    // Getter Setters

    /**
     * @brief Sets the mass of the rigidbody.
     * @param pMass The new mass.
     */
    void SetMass(float pMass);

    /**
     * @brief Gets the mass of the rigidbody.
     * @return The mass.
     */
    float GetMass() const
    {
        return mMass;
    }

    /**
     * @brief Adds a force to the rigidbody.
     * @param pForce The force vector.
     */
    void AddForce(const Vec3& pForce);

    /**
     * @brief Adds a torque to the rigidbody.
     * @param pTorque The torque vector.
     */
    void AddTorque(const Vec3& pTorque);
    
    /**
     * @brief Clears all accumulated forces.
     */
    void ClearForces();

    /**
     * @brief Clears all accumulated torques.
     */
    void ClearTorques();

    /**
     * @brief Clears all velocities, accelerations, forces, and torques.
     */
    void ClearAll();

    /**
     * @brief Gets the inverse mass.
     * @return The inverse mass.
     */
    float GetInverseMass() const
    {
        return mInverseMass;
    }

    /**
     * @brief Gets the linear velocity.
     * @return The velocity vector.
     */
    Vec3 GetVelocity() const
    {
        return mVelocity;
    }

    /**
     * @brief Gets the angular velocity.
     * @return The angular velocity vector.
     */
    Vec3 GetAngularVelocity() const
    {
        return mAngularVelocity;
    }

    /**
     * @brief Gets the moment of inertia tensor.
     * @return The moment of inertia matrix.
     */
    Mat3 GetMomentOfInertia() const
    {
        return mMomentOfInertia;
    }

    /**
     * @brief Gets the inverse moment of inertia tensor.
     * @return The inverse moment of inertia matrix.
     */
    Mat3 GetInverseMomentOfInertia() const
    {
        return mInverseMomentOfInertia;
    }

    /**
     * @brief Gets the world inverse inertia tensor.
     * @return The world inverse inertia matrix.
     */
    Mat3 GetWorldInverseIntertia() const;

    /**
     * @brief Sets the restitution (bounciness) coefficient.
     * @param pRestitution The restitution value.
     */
    void SetRestitution(float pRestitution)
    {
        mRestitution = pRestitution;
    }

    /**
     * @brief Gets the restitution (bounciness) coefficient.
     * @return The restitution value.
     */
    float GetRestitution() const
    {
        return mRestitution;
    }

    /**
     * @brief Sets the friction coefficient.
     * @param pFriction The friction value.
     */
    void SetFriction(float pFriction)
    {
        mFriction = pFriction;
    }

    /**
     * @brief Sets the angular damping factor.
     * @param pAngularDamping The angular damping value.
     */
    void SetAngularDamping(float pAngularDamping)
    {
        mAngularDamping = pAngularDamping;
    }

    /**
     * @brief Gets the friction coefficient.
     * @return The friction value.
     */
    float GetFriction() const
    {
        return mFriction;
    }

    /**
     * @brief Locks or unlocks rotation.
     * @param pLockRotation True to lock, false to unlock.
     */
    void SetLockRotation(bool pLockRotation)
    {
        mLockRotation = pLockRotation;
    }

    /**
     * @brief Gets the location of the rigidbody in world space.
     * @return The position vector.
     */
    Vec3 GetLocation() const;

    /**
     * @brief Gets the gravity scale factor.
     * @return The gravity scale.
     */
    float GetGravityScale() const
    {
        return mGravityScale;
    }

    /**
     * @brief Sets the gravity scale factor.
     * @param pGravityScale The gravity scale.
     */
    void SetGravityScale(float pGravityScale)
    {
        mGravityScale = pGravityScale;
    }

    /**
     * @brief Sets the collision component associated with this rigidbody.
     * @param pCollisionComponent Pointer to the collision component.
     */
    void SetCollisionComponent(BaseCollisionComponent* pCollisionComponent);

    /**
     * @brief Gets the collision component associated with this rigidbody.
     * @return Pointer to the collision component.
     */
    BaseCollisionComponent* GetCollisionComponent() const
    {
        return mCollisionComponent;
    }

    /**
     * @brief Gets the local axes of the rigidbody in world space.
     * @return Vector of 3 axes as Vec3.
     */
    std::vector<Vec3> GetLocalAxes() const;

    // Logic

    /**
     * @brief Applies an angular impulse to the rigidbody.
     * @param pImpulse The angular impulse vector.
     */
    void ApplyImpulseAngular(const Vec3& pImpulse);

    /**
     * @brief Applies a linear impulse to the rigidbody.
     * @param pImpulse The linear impulse vector.
     */
    void ApplyImpulseLinear(const Vec3& pImpulse);

    /**
     * @brief Applies an impulse at a specific point on the rigidbody.
     * @param pImpulse The impulse vector.
     * @param pPoint The point of application in local space.
     */
    void ApplyImpulseAtPoint(const Vec3& pImpulse, const Vec3& pPoint);

    /**
     * @brief Integrates forces to update velocity and angular velocity.
     */
    void IntegrateForces();

    /**
     * @brief Integrates velocity to update position and rotation.
     */
    void IntegrateVelocity();

    /**
     * @brief Applies an impulse to the rigidbody.
     * @param pImpulse The impulse vector.
     */
    void ApplyImpulse(const Vec3& pImpulse);

    /**
     * @brief Converts a point from world space to local space.
     * @param pPoint The point in world space.
     * @return The point in local space.
     */
    Vec3 WorldSpaceToLocalSpace(const Vec3& pPoint) const;

    /**
     * @brief Converts a point from local space to world space.
     * @param pPoint The point in local space.
     * @return The point in world space.
     */
    Vec3 LocalSpaceToWorldSpace(const Vec3& pPoint) const;

    void SetVelocityMultiplier(const Vec3& pVelocityMultiplier)
    {
        mVelocityMultiplier = pVelocityMultiplier;
    }
};
