#include "RigidbodyComponent.h"

#include "MeshComponent.h"
#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/PhysicConstants.h"
#include "Debug/Log.h"
#include "Math/Time.h"


RigidbodyComponent::RigidbodyComponent(Actor* pOwner) : Component(pOwner), mVelocity(Vec3::zero),
                                                        mAngularVelocity(Vec3::zero), mAcceleration(Vec3::zero), mAngularAcceleration(Vec3::zero),
                                                        mSumForces(Vec3::zero), mSumTorques(Vec3::zero)
{
    mRestitution = 0.5f;
    mFriction = 1.0f;
    SetMass(1.0f);
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
        float x = vertex.position.x;
        float y = vertex.position.y;
        float z = vertex.position.z;

        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;
        
        I.m[0][0] += massPerVertex * (y2 + z2);
        I.m[1][1] += massPerVertex * (x2 + z2);
        I.m[2][2] += massPerVertex * (x2 + y2);
        
        I.m[0][1] -= massPerVertex * x * y;
        I.m[0][2] -= massPerVertex * x * z;
        I.m[1][2] -= massPerVertex * y * z;
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
    if (pMass != 0.0f) mInverseMass = 1.0f / pMass;
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
    mVelocity += mAcceleration * Time::deltaTime;
    
    mAngularAcceleration = mInverseMomentOfInertia * mSumTorques;
    mAngularVelocity += mAngularAcceleration * Time::deltaTime;

    ClearForces();
    ClearTorques();
}

void RigidbodyComponent::IntegrateVelocity()
{
    if (mStatic) return;

    Vec3 location = mOwner->GetLocation();
    location += mVelocity * Time::deltaTime;
    mOwner->SetLocation(location);

    Quaternion currentRotation = mOwner->GetRotation();
    Vec3 angularIncrement = mAngularVelocity * Time::deltaTime;
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
