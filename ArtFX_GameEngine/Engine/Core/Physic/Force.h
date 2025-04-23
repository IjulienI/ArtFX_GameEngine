#pragma once

#include "Core/Render/Component/RigidbodyComponent.h"

struct Force {
	static Vec3 GenerateDragForce(const RigidbodyComponent& body, float k);

	static Vec3 GenerateFrictionForce(const RigidbodyComponent& body, float k);

	static Vec3 GenerateGravitationForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float G, float minDistance, float maxDistance);

	static Vec3 GenerateSpringForce(const RigidbodyComponent& body, Vec3 anchor, float restLenght, float k);
	static Vec3 GenerateSpringForce(const RigidbodyComponent& a, const RigidbodyComponent& b, float restLenght, float k);
};