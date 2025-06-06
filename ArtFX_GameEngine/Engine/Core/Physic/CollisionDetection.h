/**
 * @file CollisionDetection.h
 * @brief Declaration of the CollisionDetection struct, providing static methods for 3D collision detection.
 */

#pragma once

#include <vector>
#include "./Contact.h"

struct Vertex;

/**
 * @struct CollisionDetection
 * @brief Provides static methods for detecting collisions between various 3D shapes.
 */
struct CollisionDetection {
public:
    /**
     * @brief Checks if two rigidbodies are colliding and fills contact points.
     * @param a First rigidbody.
     * @param b Second rigidbody.
     * @param contacts Output vector of contacts.
     * @return True if colliding, false otherwise.
     */
    static bool IsColliding(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between two spheres.
     */
    static bool IsCollidingSphereSphere(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between two polygonal meshes.
     */
    static bool IsCollidingPolygonPolygon(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between two boxes.
     */
    static bool IsCollidingBoxBox(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between a box and a sphere.
     */
    static bool IsCollidingBoxSphere(RigidbodyComponent* box, RigidbodyComponent* sphere, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between a box and a polygonal mesh.
     */
    static bool IsCollidingBoxPolygon(RigidbodyComponent* box, RigidbodyComponent* polygon, std::vector<Contact>& contacts);

    /**
     * @brief Checks for collision between a polygonal mesh and a sphere.
     */
    static bool IsCollidingPolygonSphere(RigidbodyComponent* polygon, RigidbodyComponent* sphere, std::vector<Contact>& contacts);

private:
    /**
     * @brief Checks for overlap between two sets of vertices along a given axis.
     */
    static bool OverlapOnAxis(const std::vector<Vec3>& aVertices, const std::vector<Vec3>& bVertices, const Vec3& axis, float& overlap);

    /**
     * @brief Checks for overlap between two rigidbodies along a given axis.
     */
    static bool OverlapOnAxis(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& axis, float& overlap);

    /**
     * @brief Checks if a point is inside a triangle.
     */
    static bool IsPointInTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& p);

    /**
     * @brief Computes the contact manifold (contact points) between two sets of vertices.
     */
    static void ComputeContactManifold(const std::vector<Vec3>& aVerts, const std::vector<Vec3>& bVerts, const Vec3& collisionNormal, std::vector<Vec3>& contactPoints);
};
