#pragma once

#include <vector>
#include "./Contact.h"

struct Vertex;

struct CollisionDetection {
public:
	static bool IsColliding(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);
	static bool IsCollidingSphereSphere(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);
	static bool IsCollidingPolygonPolygon(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);
	static bool IsCollidingBoxBox(RigidbodyComponent* a, RigidbodyComponent* b, std::vector<Contact>& contacts);
	static bool IsCollidingBoxSphere(RigidbodyComponent* box, RigidbodyComponent* sphere, std::vector<Contact>& contacts);
	static bool IsCollidingBoxPolygon(RigidbodyComponent* box, RigidbodyComponent* polygon, std::vector<Contact>& contacts);
	static bool IsCollidingPolygonSphere(RigidbodyComponent* polygon, RigidbodyComponent* sphere, std::vector<Contact>& contacts);

private:
	static bool OverlapOnAxis(const std::vector<Vec3>& aVertices, const std::vector<Vec3>& bVertices, const Vec3& axis, float& overlap);
	static bool OverlapOnAxis(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& axis, float& overlap);
	static bool IsPointInTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& p);
	static void ComputeContactManifold(const std::vector<Vec3>& aVerts, const std::vector<Vec3>& bVerts, const Vec3& collisionNormal, std::vector<Vec3>& contactPoints);
};
