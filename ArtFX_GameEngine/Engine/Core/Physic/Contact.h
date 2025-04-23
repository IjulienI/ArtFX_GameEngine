#pragma once

#include "Core/Render/Component/RigidbodyComponent.h"

struct Contact {
	RigidbodyComponent* a;
	RigidbodyComponent* b;

	Vec3 start;
	Vec3 end;

	Vec3 normal;
	float depth;
};
