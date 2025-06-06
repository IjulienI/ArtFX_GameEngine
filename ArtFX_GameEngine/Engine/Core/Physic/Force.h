/**
 * @file Force.h
 * @brief Declaration of the Force struct, providing static methods to generate various physical forces.
 */

#pragma once
#include "Component/RigidbodyComponent.h"

/**
 * @struct Force
 * @brief Provides static methods to generate drag, friction, gravitation, and spring forces.
 */
struct Force {
    /**
     * @brief Generates a drag force based on velocity and drag coefficient.
     * @param body The rigidbody to apply drag to.
     * @param k The drag coefficient.
     * @return The drag force vector.
     */
    static Vec3 GenerateDragForce(const RigidbodyComponent& body, float k);

    /**
     * @brief Generates a friction force based on velocity and friction coefficient.
     * @param body The rigidbody to apply friction to.
     * @param k The friction coefficient.
     * @return The friction force vector.
     */
    static Vec3 GenerateFrictionForce(const RigidbodyComponent& body, float k);

    /**
     * @brief Generates a gravitational force between two rigidbodies.
     * @param a The first rigidbody.
     * @param b The second rigidbody.
     * @param G The gravitational constant.
     * @param minDistance Minimum distance for force calculation.
     * @param maxDistance Maximum distance for force calculation.
     * @return The gravitational force vector.
     */
    static Vec3 GenerateGravitationForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float G, float minDistance, float maxDistance);

    /**
     * @brief Generates a spring force between a rigidbody and an anchor point.
     * @param body The rigidbody.
     * @param anchor The anchor point.
     * @param restLenght The rest length of the spring.
     * @param k The spring constant.
     * @return The spring force vector.
     */
    static Vec3 GenerateSpringForce(const RigidbodyComponent& body, Vec3 anchor, float restLenght, float k);

    /**
     * @brief Generates a spring force between two rigidbodies.
     * @param a The first rigidbody.
     * @param b The second rigidbody.
     * @param restLenght The rest length of the spring.
     * @param k The spring constant.
     * @return The spring force vector.
     */
    static Vec3 GenerateSpringForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float restLenght, float k);
};
