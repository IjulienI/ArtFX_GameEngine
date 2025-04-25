#include "SphereCollisionComponent.h"

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/OpenGL/VertexArray.h"

SphereCollisionComponent::SphereCollisionComponent(Actor* actor) : BaseCollisionComponent(actor)
{
    mCollisionType = CollisionType::Sphere;   
    mRadius = actor->GetComponent<MeshComponent>()->GetMesh()->GetRadius();
    GenerateSphere(mRadius);
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
}

SphereCollisionComponent::SphereCollisionComponent(Actor* actor, float radius) : BaseCollisionComponent(actor), mRadius(radius)
{
    mCollisionType = CollisionType::Sphere;
    GenerateSphere(mRadius);
    mVertexShader.Load("Collision.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Collision.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({&mVertexShader, &mFragmentShader });
}

SphereCollisionComponent::~SphereCollisionComponent() = default;

void SphereCollisionComponent::Draw(Matrix4Row viewProj)
{
    BaseCollisionComponent::Draw(viewProj);

    Matrix4Row wt = mOwner->GetWorldTransform();    
    
    mShaderProgram.Use();
    mShaderProgram.setMatrix4Row("uViewProj", viewProj);
    mShaderProgram.setMatrix4Row("uWorldTransform", wt);

    mVertexArray->SetActive();
    glDrawArrays(GL_TRIANGLES, 0, mVertexArray->GetVerticeCount());
}

void SphereCollisionComponent::GenerateSphere(float radius)
{
    std::vector<float> vertices;
    int latitudeSegments = 6;
    int longitudeSegments = 12;

    // Génération des sommets
    for (int lat = 0; lat <= latitudeSegments; ++lat)
    {
        float theta = lat * M_PI / latitudeSegments; // Angle de latitude
        float sinTheta = sinf(theta);
        float cosTheta = cosf(theta);

        for (int lon = 0; lon <= longitudeSegments; ++lon)
        {
            float phi = lon * 2.0f * M_PI / longitudeSegments; // Angle de longitude
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            // Coordonnées cartésiennes
            float x = radius * sinTheta * cosPhi;
            float y = radius * cosTheta;
            float z = radius * sinTheta * sinPhi;

            // Normales (normalisées)
            float nx = sinTheta * cosPhi;
            float ny = cosTheta;
            float nz = sinTheta * sinPhi;

            // Coordonnées UV
            float u = static_cast<float>(lon) / longitudeSegments;
            float v = static_cast<float>(lat) / latitudeSegments;

            // Ajouter position, normale et UV
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // Création des triangles
    std::vector<float> sphereVertices;
    for (int lat = 0; lat < latitudeSegments; ++lat)
    {
        for (int lon = 0; lon < longitudeSegments; ++lon)
        {
            int first = (lat * (longitudeSegments + 1)) + lon;
            int second = first + longitudeSegments + 1;

            // Triangle 1
            for (int i : {first, second, first + 1})
            {
                sphereVertices.insert(sphereVertices.end(), 
                    vertices.begin() + i * 8, 
                    vertices.begin() + (i + 1) * 8);
            }

            // Triangle 2
            for (int i : {second, second + 1, first + 1})
            {
                sphereVertices.insert(sphereVertices.end(), 
                    vertices.begin() + i * 8, 
                    vertices.begin() + (i + 1) * 8);
            }
        }
    }

    // Création du VertexArray
    mVertexArray = new VertexArray(sphereVertices.data(), static_cast<unsigned int>(sphereVertices.size() / 8));
}

void SphereCollisionComponent::SetRadius(float radius)
{
    mRadius = radius;
    GenerateSphere(mRadius);
}

std::vector<Vec3> SphereCollisionComponent::GetVerticesInWorldSpace() const
{
    return std::vector<Vec3>();
}
