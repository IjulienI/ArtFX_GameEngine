#include "Constraint.h"

#include <algorithm>

#include "Math/Time.h"

MatMN Constraint::GetInvM() const {
    MatMN invM(12, 12);
    invM.Zero();
    
    if (a->IsStatic()) {
        invM.rows[0][0] = 0.0f;
        invM.rows[1][1] = 0.0f;
        invM.rows[2][2] = 0.0f;
    } else {
        invM.rows[0][0] = a->GetInverseMass();
        invM.rows[1][1] = a->GetInverseMass();
        invM.rows[2][2] = a->GetInverseMass();

        MatMN inverseInertiaA = a->GetInverseMomentOfInertia();
        if (inverseInertiaA.M == 0 || inverseInertiaA.N == 0) {
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    invM.rows[3 + i][3 + j] = inverseInertiaA[i][j];
                }
            }
        }
    }
    
    if (b->IsStatic()) {
        invM.rows[6][6] = 0.0f;
        invM.rows[7][7] = 0.0f;
        invM.rows[8][8] = 0.0f;
    } else {
        invM.rows[6][6] = b->GetInverseMass();
        invM.rows[7][7] = b->GetInverseMass();
        invM.rows[8][8] = b->GetInverseMass();

        MatMN inverseInertiaB = b->GetInverseMomentOfInertia();
        if (inverseInertiaB.M == 0 || inverseInertiaB.N == 0) {
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    invM.rows[9 + i][9 + j] = inverseInertiaB[i][j];
                }
            }
        }
    }
    
    return invM;
}

VecN Constraint::GetVelocities() const {
    VecN V(12);
    V.Zero();

    //Store velocities and angular velocities
    Vec3 velocityA = a->GetVelocity();
    Vec3 angularVelocityA = a->GetAngularVelocity();
    
    Vec3 velocityB = b->GetVelocity();
    Vec3 angularVelocityB = b->GetAngularVelocity();

    // Fill the velocity vector
    V[0] = velocityA.x;
    V[1] = velocityA.y;
    V[2] = velocityA.z;
    V[3] = angularVelocityA.x;
    V[4] = angularVelocityA.y;
    V[5] = angularVelocityA.z;

    V[6] = velocityB.x;
    V[7] = velocityB.y;
    V[8] = velocityB.z;
    V[9] = angularVelocityB.x;
    V[10] = angularVelocityB.y;
    V[11] = angularVelocityB.z;

    return V;
}

PenetrationConstraint::PenetrationConstraint() : Constraint(), jacobian(2, 12), cachedLambda(2), bias(0.0f) {
    cachedLambda.Zero();
    friction = 0.0f;
}

PenetrationConstraint::PenetrationConstraint(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& aCollisionPoint, const Vec3& bCollisionPoint, const Vec3& normal) : Constraint(), jacobian(2, 12), cachedLambda(2), bias(0.0f) {
    this->a = a;
    this->b = b;
    this->aPoint = a->WorldSpaceToLocalSpace(aCollisionPoint);
    this->bPoint = b->WorldSpaceToLocalSpace(bCollisionPoint);
    this->normal = a->WorldSpaceToLocalSpace(normal);
    cachedLambda.Zero();
    friction = 0.0f;
}

void PenetrationConstraint::PreSolve() {
    const Vec3 pa = a->LocalSpaceToWorldSpace(aPoint);
    const Vec3 pb = b->LocalSpaceToWorldSpace(bPoint);
    Vec3 n = a->LocalSpaceToWorldSpace(normal);

    const Vec3 ra = pa - a->GetLocation();
    const Vec3 rb = pb - b->GetLocation();

    jacobian.Zero();
    
    const Vec3 crossRaN = Vec3::Cross(ra, n);
    const Vec3 crossRbN = Vec3::Cross(rb, n);
    
    jacobian.rows[0][0] = -n.x;
    jacobian.rows[0][1] = -n.y;
    jacobian.rows[0][2] = -n.z;    
    jacobian.rows[0][3] = -crossRaN.x;
    jacobian.rows[0][4] = -crossRaN.y;
    jacobian.rows[0][5] = -crossRaN.z;
    jacobian.rows[0][6] = n.x;
    jacobian.rows[0][7] = n.y;
    jacobian.rows[0][8] = n.z;    
    jacobian.rows[0][9] = crossRbN.x;
    jacobian.rows[0][10] = crossRbN.y;
    jacobian.rows[0][11] = crossRbN.z;

    friction = std::max(a->GetFriction(), b->GetFriction());
    if (friction > 0.0f) {
        Vec3 t = Vec3::Normalize(n);
        
        const Vec3 crossRaT = Vec3::Cross(ra, t);
        const Vec3 crossRbT = Vec3::Cross(rb, t);
        
        jacobian.rows[1][0] = -t.x;
        jacobian.rows[1][1] = -t.y;
        jacobian.rows[1][2] = -t.z;        
        jacobian.rows[1][3] = -crossRaT.x;
        jacobian.rows[1][4] = -crossRaT.y;
        jacobian.rows[1][5] = -crossRaT.z;
        jacobian.rows[1][6] = t.x;
        jacobian.rows[1][7] = t.y;
        jacobian.rows[1][8] = t.z;        
        jacobian.rows[1][9] = crossRbT.x;
        jacobian.rows[1][10] = crossRbT.y;
        jacobian.rows[1][11] = crossRbT.z;
    }

    // Warm start
    const MatMN Jt = jacobian.Transpose();
    VecN impulses = Jt * cachedLambda;

    a->ApplyImpulseLinear(Vec3(impulses[0], impulses[1], impulses[2]));
    a->ApplyImpulseAngular(Vec3(impulses[3], impulses[4], impulses[5]));
    b->ApplyImpulseLinear(Vec3(impulses[6], impulses[7], impulses[8]));
    b->ApplyImpulseAngular(Vec3(impulses[9], impulses[10], impulses[11]));

    const float beta = 0.2f;
    float C = Vec3::Dot(pb - pa, n);
    C = std::min(0.0f, C + 0.01f);

    Vec3 va = a->GetVelocity() +  Vec3::Cross(a->GetAngularVelocity(), ra);
    Vec3 vb = b->GetVelocity() +  Vec3::Cross(b->GetAngularVelocity(), rb);
    float vrelDotNormal = Vec3::Dot(va - vb, n);    

    float e = std::min(a->GetRestitution(), b->GetRestitution());

    bias = (beta / Time::deltaTime) * C + (e * vrelDotNormal);
}

void PenetrationConstraint::Solve() {
    const VecN V = GetVelocities();
    const MatMN invM = GetInvM();

    const MatMN J = jacobian;
    const MatMN Jt = jacobian.Transpose();

    MatMN lhs = J * invM * Jt;
    VecN rhs = J * V * -1.0f;
    rhs[0] -= bias;
    VecN lambda = MatMN::SolveGaussSeidel(lhs, rhs);

    VecN oldLambda = cachedLambda;
    cachedLambda += lambda;
    cachedLambda[0] = (cachedLambda[0] < 0.0f) ? 0.0f : cachedLambda[0];

    if (friction > 0.0) {
        const float maxFriction = cachedLambda[0] * friction;
        cachedLambda[1] = std::clamp(cachedLambda[1], -maxFriction, maxFriction);
    }

    lambda = cachedLambda - oldLambda;

    VecN impulses = Jt * lambda;

    a->ApplyImpulseLinear(Vec3(impulses[0], impulses[1], impulses[2]));
    a->ApplyImpulseAngular(Vec3(impulses[3], impulses[4], impulses[5]));
    b->ApplyImpulseLinear(Vec3(impulses[6], impulses[7], impulses[8]));
    b->ApplyImpulseAngular(Vec3(impulses[9], impulses[10], impulses[11]));
}

void PenetrationConstraint::PostSolve() {
}
