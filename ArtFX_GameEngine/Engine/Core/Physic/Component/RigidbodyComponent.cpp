#include "RigidbodyComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/PhysicConstants.h"
#include "Core/Render/Component/MeshComponent.h"


RigidbodyComponent::RigidbodyComponent(Actor* pOwner) : Component(pOwner), mVelocity(Vec3::zero),
                                                        mAngularVelocity(Vec3::zero), mAcceleration(Vec3::zero), mAngularAcceleration(Vec3::zero),
                                                        mSumForces(Vec3::zero), mSumTorques(Vec3::zero)
{
    mRestitution = 0.0f;
    mFriction = 1.0f;
    mAngularDamping = 0.4f;
    SetMass(100.0f);
    CalcMomentOfInertia();
}

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

void RigidbodyComponent::OnStart()
{
    Component::OnStart();
}

void RigidbodyComponent::Update()
{
    Component::Update();
}

void RigidbodyComponent::OnEnd()
{
    Component::OnEnd();
}

bool RigidbodyComponent::IsStatic() const
{
    return fabs(mInverseMass - 0.0f) < EPSILON;
}

void RigidbodyComponent::SetMass(float pMass)
{
    mMass = pMass;
    if (pMass > 0.0f) mInverseMass = 1.0f / pMass;
    else mInverseMass = 0.0f;
    mStatic = IsStatic();
    CalcMomentOfInertia();
}

void RigidbodyComponent::AddForce(const Vec3& pForce)
{
    mSumForces += pForce;
}

void RigidbodyComponent::AddTorque(const Vec3& pTorque)
{
    mSumTorques += pTorque;
}

void RigidbodyComponent::ClearForces()
{
    mSumForces = Vec3::zero;
}

void RigidbodyComponent::ClearTorques()
{
    mSumTorques = Vec3::zero;
}

void RigidbodyComponent::ClearAll()
{
    mVelocity = Vec3::zero;
    mAngularVelocity = Vec3::zero;
    mAcceleration = Vec3::zero;
    mAngularAcceleration = Vec3::zero;
    mSumForces = Vec3::zero;
    mSumTorques = Vec3::zero;
}

Mat3 RigidbodyComponent::GetWorldInverseIntertia() const
{
    Mat3 R = Mat3::CreateFromQuaternion(mOwner->GetRotation());
    Mat3 I_local_inv = mInverseMomentOfInertia;
    return R * I_local_inv * R.Transpose();
}

Vec3 RigidbodyComponent::GetLocation() const
{
    return mOwner->GetLocation();
}

void RigidbodyComponent::SetCollisionComponent(BaseCollisionComponent* pCollisionComponent)
{
    mCollisionComponent = pCollisionComponent;
}

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

void RigidbodyComponent::ApplyImpulseAngular(const Vec3& pImpulse)
{
    if (mStatic) return;

    mAngularVelocity += mInverseMomentOfInertia * pImpulse;
}

void RigidbodyComponent::ApplyImpulseLinear(const Vec3& pImpulse)
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
}

void RigidbodyComponent::ApplyImpulseAtPoint(const Vec3& pImpulse, const Vec3& pPoint)
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
    mAngularVelocity += mInverseMomentOfInertia * Vec3::Cross(pImpulse, pPoint);
}

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

void RigidbodyComponent::IntegrateVelocity()
{
    if (mStatic) return;

    Vec3 location = mOwner->GetLocation();
    location += mVelocity * DELTA_STEP;
    mOwner->SetLocation(location);

    mVelocity *= (1.0f - DELTA_STEP * mFriction / mMass);
    //mAngularVelocity *= (1.0f - DELTA_STEP * mAngularDamping / mMass);

    Quaternion currentRotation = mOwner->GetRotation();
    Vec3 angularIncrement = mAngularVelocity * DELTA_STEP;
    Quaternion rotationDelta(Vec3::Normalize(angularIncrement), angularIncrement.Length());
    Quaternion rotation = Quaternion::Concatenate(currentRotation, rotationDelta);
    mOwner->SetRotation(rotation);
}

void RigidbodyComponent::ApplyImpulse(const Vec3& pImpulse) 
{
    if (mStatic) return;

    mVelocity += pImpulse * mInverseMass;
}

Vec3 RigidbodyComponent::WorldSpaceToLocalSpace(const Vec3& pPoint) const
{
    Vec3 translation = pPoint - mOwner->GetLocation();

    Quaternion inverseRotation = mOwner->GetRotation().Inverse();
    Vec3 rotated = inverseRotation * translation;

    return rotated;
}

Vec3 RigidbodyComponent::LocalSpaceToWorldSpace(const Vec3& pPoint) const
{
    Quaternion rotation = mOwner->GetRotation();
    Vec3 rotated = rotation * pPoint;
    return rotated + mOwner->GetLocation();
}
