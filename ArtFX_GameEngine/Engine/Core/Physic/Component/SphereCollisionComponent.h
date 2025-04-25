#pragma once
#include "BaseCollisionComponent.h"
#include "Core/Render/Shader/ShaderProgram.h"

class VertexArray;

class SphereCollisionComponent : public BaseCollisionComponent
{
private:
    float mRadius;
    Vec3 mCenter;

    VertexArray* mVertexArray;
    ShaderProgram mShaderProgram;
    Shader mVertexShader, mFragmentShader;
public:
    SphereCollisionComponent(Actor* actor);
    SphereCollisionComponent(Actor* actor, float radius);
    ~SphereCollisionComponent() override;

    void Draw(Matrix4Row viewProj) override;

    void GenerateSphere(float radius);

    void SetRadius(float radius);
    float GetRadius() const
    {
        return mRadius;
    }

    std::vector<Vec3> GetVerticesInWorldSpace() const override;
};
