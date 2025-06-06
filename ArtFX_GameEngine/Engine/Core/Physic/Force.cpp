/**
 * @file Force.cpp
 * @brief Implementation of the Force struct's static methods for generating physical forces.
 */

#include "Force.h"

#include <algorithm>

Vec3 Force::GenerateDragForce(const RigidbodyComponent& body, float k)
{
    Vec3 dragForce = Vec3::zero;
    if (body.GetVelocity().LengthSq() > 0) {
        Vec3 dragDirection = body.GetVelocity().UnitVector() * -1.0;
        float dragMagnitude = k * body.GetVelocity().LengthSq();

        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vec3 Force::GenerateFrictionForce(const RigidbodyComponent& body, float k)
{
    Vec3 frictionDirection = body.GetVelocity().UnitVector() * -1.0;
    float frictionMagnitude = k;

    return frictionDirection * frictionMagnitude;
}

Vec3 Force::GenerateGravitationForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float G,
    float minDistance, float maxDistance)
{
    Vec3 d = (b.GetLocation() - a.GetLocation());
    float distanceSquared = d.LengthSq();
    
    distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

    Vec3 attractionDirection = d.UnitVector();
    float attractionMagnitude = G * (a.GetMass() * b.GetMass()) / distanceSquared;

    Vec3 attractionForce = attractionDirection * attractionMagnitude;

    return attractionForce;
}

Vec3 Force::GenerateSpringForce(const RigidbodyComponent& body, Vec3 anchor, float restLenght, float k)
{
    Vec3 d = body.GetLocation() - anchor;
    float displacement = d.Length() - restLenght;
    Vec3 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec3 springForce = springDirection * springMagnitude;

    return springForce;
}

Vec3 Force::GenerateSpringForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float restLenght, float k)
{
    Vec3 d = a.GetLocation() - b.GetLocation();
    float displacement = d.Length() - restLenght;
    Vec3 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec3 springForce = springDirection * springMagnitude;

    return springForce;
}
