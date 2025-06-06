/**
 * @file Constraint.h
 * @brief Declaration of the Constraint and PenetrationConstraint classes for physics constraints.
 */

#pragma once

#include "Component/RigidbodyComponent.h"
#include "Math/MatMN.h"

/**
 * @class Constraint
 * @brief Base class for physics constraints between two rigidbodies.
 */
class Constraint {
public:
    /**
     * @brief Pointer to the first rigidbody.
     */
    RigidbodyComponent* a;

    /**
     * @brief Pointer to the second rigidbody.
     */
    RigidbodyComponent* b;

    /**
     * @brief Contact point on rigidbody a (in local space).
     */
    Vec3 aPoint;

    /**
     * @brief Contact point on rigidbody b (in local space).
     */
    Vec3 bPoint;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Constraint() = default;

    /**
     * @brief Gets the inverse mass matrix for the constraint.
     * @return The inverse mass matrix.
     */
    MatMN GetInvM() const;

    /**
     * @brief Gets the velocity vector for the constraint.
     * @return The velocity vector.
     */
    VecN GetVelocities() const;

    /**
     * @brief Prepares the constraint before solving.
     */
    virtual void PreSolve() {};

    /**
     * @brief Solves the constraint.
     */
    virtual void Solve() {};

    /**
     * @brief Finalizes the constraint after solving.
     */
    virtual void PostSolve() {};
};

/**
 * @class PenetrationConstraint
 * @brief Constraint that resolves penetration between two rigidbodies.
 */
class PenetrationConstraint : public Constraint {
private:
    /**
     * @brief Jacobian matrix for the constraint.
     */
    MatMN jacobian;

    /**
     * @brief Cached lambda values for iterative solving.
     */
    VecN cachedLambda;

    /**
     * @brief Bias term for Baumgarte stabilization.
     */
    float bias;

    /**
     * @brief Contact normal vector.
     */
    Vec3 normal;

    /**
     * @brief Friction coefficient.
     */
    float friction;

public:
    /**
     * @brief Default constructor.
     */
    PenetrationConstraint();

    /**
     * @brief Constructs a penetration constraint between two rigidbodies.
     * @param a Pointer to the first rigidbody.
     * @param b Pointer to the second rigidbody.
     * @param aCollisionPoint Collision point on a.
     * @param bCollisionPoint Collision point on b.
     * @param normal Contact normal.
     */
    PenetrationConstraint(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& aCollisionPoint, const Vec3& bCollisionPoint, const Vec3& normal);

    /**
     * @brief Prepares the constraint before solving.
     */
    void PreSolve() override;

    /**
     * @brief Solves the constraint.
     */
    void Solve() override;

    /**
     * @brief Finalizes the constraint after solving.
     */
    void PostSolve() override;
};
