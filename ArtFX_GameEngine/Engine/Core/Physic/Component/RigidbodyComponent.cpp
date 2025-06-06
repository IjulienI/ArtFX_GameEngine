/**
 * @file RigidbodyComponent.cpp
 * @brief Implementation of the RigidbodyComponent class, which handles physics simulation for an Actor.
 */

#include "RigidbodyComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/PhysicConstants.h"
#include "Core/Render/Component/MeshComponent.h"

/**
 * @brief Constructs a RigidbodyComponent and initializes its physical properties.
 * @param pOwner Pointer to the owning Actor.
 */
RigidbodyComponent::RigidbodyComponent(Actor* pOwner) : Component(pOwner), mVelocity(Vec3::zero),
                                                        mAngularVelocity(Vec3::zero), mAcceleration(Vec3::zero), mAngularAcceleration(Vec3::zero),
                                                        mSumForces(Vec3::zero), mSumTorques(Vec3::zero)
{
    mRestitution = 0.0f;
    mFriction = 1.0f;
    mAngularDamping = 0.4f;
    mLinearDamping = 0.4f;
    SetMass(100.0f);
    CalcMomentOfInertia();
}

/**
 * @brief Calculates the moment of inertia tensor based on the mesh vertices.
 */
void RigidbodyComponent::CalcMomentOfInertia()
{
    const Mesh* mesh = mOwner->GetComponent<MeshComponent>()->GetMesh();
    const std::vector<Vertex>& vertices = mesh->GetVertices();
    size_t vertexCount = vertices.size();

    if (vertexCount == 0) return;

    float totalMass = mMass;
    float massPerVertex = totalMass / static_cast<float>(vertexCount);

    Mat3 I;
    for (auto& vertex : vertices)
    {
        Vec3 vertexPos = vertex.position;

        Vec3 vertexPos2 = vertex.position * vertex.position;
        
        I.m[0][0] += massPerVertex * (vertexPos2.y + vertexPos2.z);
        I.m[1][1] += massPerVertex * (vertexPos2.x + vertexPos2.z);
        I.m[2][2] += massPerVertex * (vertexPos2.x + vertexPos2.y);
        
        I.m[0][1] -= massPerVertex * vertexPos.x * vertexPos.y;
        I.m[0][2] -= massPerVertex * vertexPos.x * vertexPos.z;
        I.m[1][2] -= massPerVertex * vertexPos.y * vertexPos.z;
    }
    
    I.m[1][0] = I.m[0][1];
    I.m[2][0] = I.m[0][2];
    I.m[2][1] = I.m[1][2];

    mMomentOfInertia = I;
    mInverseMomentOfInertia = I.Inverse();
}

/**
 * @brief Called when the component is started.
 */
void RigidbodyComponent::OnStart()
{
    Component::OnStart();
}

/**
 * @brief Updates the rigidbody component every frame.
 */
void RigidbodyComponent::Update()
{
    Component::Update();
}

/**
 * @brief Called when the component is about to be destroyed or removed.
 */
void RigidbodyComponent::OnEnd()
{
    Component::OnEnd();
}

/**
 * @brief Checks if the rigidbody is static (immovable).
 * @return True if static, false otherwise.
 */
bool RigidbodyComponent::IsStatic() const
{
    return fabs(mInverseMass - 0.0f) < EPSILON;
}

/**
 * @brief Sets the mass of the rigidbody and recalculates inertia.
 * @param pMass The new mass.
 */
void RigidbodyComponent::SetMass(float pMass)
{
    mMass = pMass;
    if (pMass > 0.0f) mInverseMass = 1.0f / pMass;
    else mInverseMass = 0.0f;
    mStatic = IsStatic();
    CalcMomentOfInertia();
}

/**
 * @brief Adds a force to the rigidbody.
 * @param pForce The force vector.
 */
void RigidbodyComponent::AddForce(const Vec3& pForce)
{
    mSumForces += pForce;
}

/**
 * @brief Adds a torque to the rigidbody.
 * @param pTorque The torque vector.
 */
void RigidbodyComponent::AddTorque(const Vec3& pTorque)
{
    mSumTorques += pTorque;
}

/**
 * @brief Clears all accumulated forces.
 */
void RigidbodyComponent::ClearForces()
{
    mSumForces = Vec3::zero;
}

/**
 * @brief Clears all accumulated torques.
 */
void RigidbodyComponent::ClearTorques()
{
    mSumTorques = Vec3::zero;
}

/**
 * @brief Clears all velocities, accelerations, forces, and torques.
 */
void RigidbodyComponent::ClearAll()
{
    mVelocity = Vec3::zero;
    mAngularVelocity = Vec3::zero;
    mAcceleration = Vec3::zero;
    mAngularAcceleration = Vec3::zero;
    mSumForces = Vec3::zero;
    mSumTorques = Vec3::zero;
}

/**
 * @brief Gets the world inverse inertia tensor.
 * @return The world inverse inertia matrix.
 */
Mat3 RigidbodyComponent::GetWorldInverseIntertia() const
{
    Mat3 R = Mat3::CreateFromQuaternion(mOwner->GetRotation());
    Mat3 I_local_inv = mInverseMomentOfInertia;
    return R * I_local_inv * R.Transpose();
}

/**
 * @brief Gets the location of the rigidbody in world space.
 * @return The position vector.
 */
Vec3 RigidbodyComponent::GetLocation() const
{
    return mOwner->GetLocation();
}

/**
 * @brief Sets the collision component associated with this rigidbody.
 * @param pCollisionComponent Pointer to the collision component.
 */
void RigidbodyComponent::SetCollisionComponent(BaseCollisionComponent* pCollisionComponent)
{
    mCollisionComponent = pCollisionComponent;
}

/**
 * @brief Gets the local axes of the rigidbody in world space.
 * @return Vector of 3 axes as Vec3.
 */
std::vector<Vec3> RigidbodyComponent::GetLocalAxes() const
{
    Quaternion rotation = mOwner->GetRotation();

    Vec3 localX(1, 0, 0);
    Vec3 localY(0, 1, 0);
    Vec3 localZ(0, 0, 1);
    
    Vec3 worldX = rotation * localX;
    Vec3 worldY = rotation * localY;
    Vec3 worldZ = rotation * localZ;

    return { worldX, worldY, worldZ };
}

/**
 * @brief Applies an angular impulse to the rigidbody.
 * @param pImpulse The angular impulse vector.
 */
void RigidbodyComponent::ApplyImpulseAngular(const Vec3& pImpulse)
{
    if (mStatic) return;

    mAngularVelocity += mInverseMomentOfInertia * pImpulse;
}

/**
 * @brief Applies a linear impulse to the rigidbody.
 * @param pImpulse The linear impulse vector.
 */
void RigidbodyComponent::ApplyImpulseLinear(const Vec3& pImpulse)
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
}

/**
 * @brief Applies an impulse at a specific point on the rigidbody.
 * @param pImpulse The impulse vector.
 * @param pPoint The point of application in local space.
 */
void RigidbodyComponent::ApplyImpulseAtPoint(const Vec3& pImpulse, const Vec3& pPoint)
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
    mAngularVelocity += mInverseMomentOfInertia * Vec3::Cross(pImpulse, pPoint);
}

/**
 * @brief Integrates forces to update velocity and angular velocity.
 */
void RigidbodyComponent::IntegrateForces()
{
    if (mStatic) return;

    mAcceleration = mSumForces * mInverseMass;
    mVelocity += mAcceleration * DELTA_STEP;
    
    mAngularAcceleration = mInverseMomentOfInertia * mSumTorques;
    mAngularVelocity += mAngularAcceleration * DELTA_STEP;
    
    ClearForces();
    ClearTorques();
}

/**
 * @brief Integrates velocity to update position and rotation.
 */
void RigidbodyComponent::IntegrateVelocity()
{
    if (mStatic) return;

    Vec3 location = mOwner->GetLocation();
    location += mVelocity * DELTA_STEP;
    mOwner->SetLocation(location);

    mVelocity *= (1.0f - DELTA_STEP * mLinearDamping / mMass);
    if (!mLockRotation)
    {
        mAngularVelocity *= (1.0f - DELTA_STEP * mAngularDamping / mMass);
        Quaternion currentRotation = mOwner->GetRotation();
        Vec3 angularIncrement = mAngularVelocity * DELTA_STEP;
        Quaternion rotationDelta(Vec3::Normalize(angularIncrement), angularIncrement.Length());
        Quaternion rotation = Quaternion::Concatenate(currentRotation, rotationDelta);
        mOwner->SetRotation(rotation);
    }    
}

/**
 * @brief Applies an impulse to the rigidbody.
 * @param pImpulse The impulse vector.
 */
void RigidbodyComponent::ApplyImpulse(const Vec3& pImpulse) 
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
}

/**
 * @brief Converts a point from world space to local space.
 * @param pPoint The point in world space.
 * @return The point in local space.
 */
Vec3 RigidbodyComponent::WorldSpaceToLocalSpace(const Vec3& pPoint) const
{
    Vec3 translation = pPoint - mOwner->GetLocation();

    Quaternion inverseRotation = mOwner->GetRotation().Inverse();
    Vec3 rotated = inverseRotation * translation;

    return rotated;
}

/**
 * @brief Converts a point from local space to world space.
 * @param pPoint The point in local space.
 * @return The point in world space.
 */
Vec3 RigidbodyComponent::LocalSpaceToWorldSpace(const Vec3& pPoint) const
{
    Quaternion rotation = mOwner->GetRotation();
    Vec3 rotated = rotation * pPoint;
    return rotated + mOwner->GetLocation();
}
