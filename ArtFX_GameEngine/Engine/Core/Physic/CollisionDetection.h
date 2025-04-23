#pragma once

#include <vector>
#include "./Contact.h"
#include "Core/Render/Component/RigidbodyComponent.h"

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
};
