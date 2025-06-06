/**
 * @file Constraint.cpp
 * @brief Implementation of the Constraint and PenetrationConstraint classes for physics constraints.
 */

#include "Constraint.h"

#include <algorithm>
#include <numbers>

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

        Mat3 inverseInertiaA = a->GetInverseMomentOfInertia();
        if (inverseInertiaA.m[0][0] == 0.0f || inverseInertiaA.m[1][1] == 0.0f) {
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    invM.rows[3 + i][3 + j] = inverseInertiaA.m[i][j];
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

        Mat3 inverseInertiaB = b->GetInverseMomentOfInertia();
        if (inverseInertiaB.m[0][0] == 0.0f || inverseInertiaB.m[1][1] == 0.0f) {
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    invM.rows[9 + i][9 + j] = inverseInertiaB.m[i][j];
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

PenetrationConstraint::PenetrationConstraint() : Constraint(), jacobian(3, 12), cachedLambda(3), bias(0.0f) {
    cachedLambda.Zero();
    friction = 0.0f;
}

PenetrationConstraint::PenetrationConstraint(RigidbodyComponent* a, RigidbodyComponent* b, const Vec3& aCollisionPoint, const Vec3& bCollisionPoint, const Vec3& normal) : Constraint(), jacobian(3, 12), cachedLambda(3), bias(0.0f) {
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
    Vec3 n = Vec3::Normalize(a->LocalSpaceToWorldSpace(normal));

    const Vec3 ra = pa - a->GetLocation();
    const Vec3 rb = pb - b->GetLocation();
    
    Vec3 t1;
    if (std::abs(n.x) < std::numbers::egamma_v<float>)
        t1 = Vec3::Cross(n, Vec3::unitX);
    else
        t1 = Vec3::Cross(n, Vec3::unitY);
    t1 = Vec3::Normalize(t1);
    Vec3 t2 = Vec3::Cross(n, t1);

    jacobian = MatMN(3, 12);
    cachedLambda = VecN(3);
    cachedLambda.Zero();

    Vec3 dirs[3] = { n, t1, t2 };

    for (int row = 0; row < 3; ++row) {
        const Vec3& dir = dirs[row];
        Vec3 raCross = Vec3::Cross(ra, dir);
        Vec3 rbCross = Vec3::Cross(rb, dir);

        jacobian[row][0]  = -dir.x;
        jacobian[row][1]  = -dir.y;
        jacobian[row][2]  = -dir.z;
        jacobian[row][3]  = -raCross.x;
        jacobian[row][4]  = -raCross.y;
        jacobian[row][5]  = -raCross.z;

        jacobian[row][6]  =  dir.x;
        jacobian[row][7]  =  dir.y;
        jacobian[row][8]  =  dir.z;
        jacobian[row][9]  =  rbCross.x;
        jacobian[row][10] =  rbCross.y;
        jacobian[row][11] =  rbCross.z;
    }
    
    const MatMN Jt = jacobian.Transpose();
    VecN impulses = Jt * cachedLambda;

    a->ApplyImpulseLinear(Vec3(impulses[0], impulses[1], impulses[2]));
    a->ApplyImpulseAngular(Vec3(impulses[3], impulses[4], impulses[5]));
    b->ApplyImpulseLinear(Vec3(impulses[6], impulses[7], impulses[8]));
    b->ApplyImpulseAngular(Vec3(impulses[9], impulses[10], impulses[11]));
    
    friction = std::max(a->GetFriction(), b->GetFriction());
    
    const float beta = 0.2f;
    float C = Vec3::Dot(pb - pa, n);
    C = std::min(0.0f, C + 0.01f);

    Vec3 va = a->GetVelocity() + Vec3::Cross(a->GetAngularVelocity(), ra);
    Vec3 vb = b->GetVelocity() + Vec3::Cross(b->GetAngularVelocity(), rb);
    float vrelDotNormal = Vec3::Dot(va - vb, n);

    float e = std::min(a->GetRestitution(), b->GetRestitution());
    bias = (beta / DELTA_STEP) * C + (e * vrelDotNormal);
}

void PenetrationConstraint::Solve() {
    const VecN V = GetVelocities();
    const MatMN invM = GetInvM();

    const MatMN J = jacobian;
    const MatMN Jt = J.Transpose();

    MatMN lhs = J * invM * Jt;
    VecN rhs = J * V * -1.0f;
    rhs[0] -= bias;

    VecN lambda = MatMN::SolveGaussSeidel(lhs, rhs);

    VecN oldLambda = cachedLambda;
    cachedLambda += lambda;

    // Clamp pour la normale
    cachedLambda[0] = std::max(0.0f, cachedLambda[0]);

    // Gestion de la friction
    if (friction > 0.0f) {
        float maxFriction = cachedLambda[0] * friction;

        // Clamp des composantes tangentielles
        cachedLambda[1] = std::clamp(cachedLambda[1], -maxFriction, maxFriction);
        cachedLambda[2] = std::clamp(cachedLambda[2], -maxFriction, maxFriction);
    } else {
        cachedLambda[1] = 0.0f;
        cachedLambda[2] = 0.0f;
    }

    // Calcul des impulsions
    lambda = cachedLambda - oldLambda;
    VecN impulses = Jt * lambda;

    // Application des impulsions
    a->ApplyImpulseLinear(Vec3(impulses[0], impulses[1], impulses[2]));
    a->ApplyImpulseAngular(Vec3(impulses[3], impulses[4], impulses[5]));
    b->ApplyImpulseLinear(Vec3(impulses[6], impulses[7], impulses[8]));
    b->ApplyImpulseAngular(Vec3(impulses[9], impulses[10], impulses[11]));
}

void PenetrationConstraint::PostSolve() {
}
