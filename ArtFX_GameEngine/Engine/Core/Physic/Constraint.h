#pragma once

#include "Core/Render/Component/RigidbodyComponent.h"
#include "Math/MatMN.h"

class Constraint {
public:
	RigidbodyComponent* a;
	RigidbodyComponent* b;

	Vec3 aPoint;
	Vec3 bPoint;

	virtual ~Constraint() = default;

	MatMN GetInvM() const;
	VecN GetVelocities() const;

	virtual void PreSolve() {};
	virtual void Solve() {};
	virtual void PostSolve() {};
};

class PenetrationConstraint : public Constraint {
private:
	MatMN jacobian;
	VecN cachedLambda;
	float bias;

	Vec3 normal;
	float friction;

public:
	PenetrationConstraint();
	PenetrationConstraint(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& aCollisionPoint, const Vec3& bCollisionPoint, const Vec3& normal);
	void PreSolve() override;
	void Solve() override;
	void PostSolve() override;
};