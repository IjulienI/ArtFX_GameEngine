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
    SetMass(100.0f);
    CalcMomentOfInertia();
}

void RigidbodyComponent::CalcMomentOfInertia()
{
    const Mesh* mesh = mOwner->GetComponent<MeshComponent>()->GetMesh();

    mMomentOfInertia.Zero();

    float totalMass = mMass;

    const std::vector<Vertex>& vertices = mesh->GetVertices();
    size_t vertexCount = mesh->GetVerticesCount();
    if (vertexCount == 0) return;

    float massPerVertex = totalMass / static_cast<float>(vertexCount);

    for (auto& vertex : vertices)
    {
        float x2 = vertex.position.x * vertex.position.x;
        float y2 = vertex.position.y * vertex.position.y;
        float z2 = vertex.position.z * vertex.position.z;

        mMomentOfInertia.rows[0][0] += massPerVertex * (y2 + z2);
        mMomentOfInertia.rows[1][1] += massPerVertex * (x2 + z2);
        mMomentOfInertia.rows[2][2] += massPerVertex * (x2 + y2);

        mMomentOfInertia.rows[0][1] -= massPerVertex * vertex.position.x * vertex.position.y;
        mMomentOfInertia.rows[0][2] -= massPerVertex * vertex.position.x * vertex.position.z;
        mMomentOfInertia.rows[1][2] -= massPerVertex * vertex.position.x * vertex.position.y;
    }

    mMomentOfInertia.rows[1][0] = mMomentOfInertia.rows[0][1];
    mMomentOfInertia.rows[2][0] = mMomentOfInertia.rows[0][2];
    mMomentOfInertia.rows[2][1] = mMomentOfInertia.rows[1][2];

    mInverseMomentOfInertia = mMomentOfInertia.Inverse();
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
    
    mAngularVelocity += pImpulse * mInverseMass;
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
    mAngularVelocity += Vec3::Cross(pImpulse,pPoint) * mInverseMass;
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
    if (angularIncrement.LengthSq() > EPSILON)
    {        
        Quaternion rotationDelta(Vec3::Normalize(angularIncrement), angularIncrement.Length());
        Quaternion rotation = Quaternion::Concatenate(currentRotation, rotationDelta);
        mOwner->SetRotation(rotation);
    }           
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
