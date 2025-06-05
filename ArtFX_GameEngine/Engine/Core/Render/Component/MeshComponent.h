#pragma once
#include "Core/Class/Component/Component.h"
#include "Core/Class/Mesh/Mesh.h"

class MeshComponent : public Component
{
protected:
    Mesh* mMesh;
    size_t mTextureIndex;

    bool mVisible = true;
    bool mUseTessellation = false;
    float mDisplacementScale = 1.0f;

    int mTessellationLevel = 1;
    Vec2 mTiling = Vec2(1.0f, 1.0f);
    float mTime = 0.0f;
    
public:
    MeshComponent(Actor* pOwner);
    virtual ~MeshComponent();
    virtual void Draw(Matrix4Row viewProj);

    //Getter Setters
    virtual void SetMesh(Mesh& mesh);
    void SetTextureIndex(size_t pTextureIndex);
    void AddTexture(Texture& pTexture);
    void SetVisible(bool pVisible);
    bool GetVisible() const
    {
        return mVisible;
    }
    Mesh* GetMesh() const
    {
        return mMesh;
    }

    void SetUseTessellation(bool pUseTessellation)
    {
        mUseTessellation = pUseTessellation;
    }

    void SetDisplacementScale(float pDisplacementScale)
    {
        mDisplacementScale = pDisplacementScale;
    }

    void SetTessellationLevel(int pTessellationLevel)
    {
        mTessellationLevel = pTessellationLevel;
    }

    void SetTiling(const Vec2& pTiling)
    {
        mTiling = pTiling;
    }
};
