/**
 * @file Contact.h
 * @brief Defines the Contact struct, representing a contact point between two rigidbodies.
 */

#pragma once
#include "Component/RigidbodyComponent.h"

/**
 * @struct Contact
 * @brief Represents a contact point between two rigidbodies, including contact points, normal, and penetration depth.
 */
struct Contact {
    /**
     * @brief Pointer to the first rigidbody in contact.
     */
    RigidbodyComponent* a;

    /**
     * @brief Pointer to the second rigidbody in contact.
     */
    RigidbodyComponent* b;

    /**
     * @brief Start point of the contact (on object a).
     */
    Vec3 start;

    /**
     * @brief End point of the contact (on object b).
     */
    Vec3 end;

    /**
     * @brief Contact normal vector.
     */
    Vec3 normal;

    /**
     * @brief Penetration depth.
     */
    float depth;
};
