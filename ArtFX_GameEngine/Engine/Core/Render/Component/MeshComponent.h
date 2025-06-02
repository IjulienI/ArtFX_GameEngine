#pragma once
#include "Core/Class/Component/Component.h"
#include "Core/Class/Mesh/Mesh.h"

class MeshComponent : public Component
{
protected:
    Mesh* mMesh;
    size_t mTextureIndex;

    bool mVisible;
    bool mUseTessellation;

    int mTessellationLevel;
    
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

    void SetTessellationLevel(int pTessellationLevel)
    {
        mTessellationLevel = pTessellationLevel;
    }
};
