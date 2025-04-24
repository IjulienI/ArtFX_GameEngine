#pragma once
#include "BaseCollisionComponent.h"
#include "Core/Class/Mesh/Mesh.h"

class BoxCollisionComponent : public BaseCollisionComponent
{
protected:
    Box mBoundingBox;

    VertexArray* mVertexArray;
    ShaderProgram mShaderProgram;
    Shader mVertexShader, mFragmentShader;
public:
    BoxCollisionComponent(Actor* owner);
    BoxCollisionComponent(Actor* owner, const Box box);
    virtual ~BoxCollisionComponent();

    void Draw(Matrix4Row viewProj) override;

    void SetBoundingBox(const Box& box);
    Box GetBoundingBox() const
    {
        return mBoundingBox;
    }

    void GenerateBox();
};
