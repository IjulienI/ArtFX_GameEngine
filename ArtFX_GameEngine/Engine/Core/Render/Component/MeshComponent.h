/**
 * @file MeshComponent.h
 * @brief Declaration of the MeshComponent class, which handles rendering of meshes attached to an Actor.
 */

#pragma once
#include "Core/Class/Component/Component.h"
#include "Core/Class/Mesh/Mesh.h"

/**
 * @class MeshComponent
 * @brief Component responsible for rendering meshes attached to an Actor.
 */
class MeshComponent : public Component
{
protected:
    /**
     * @brief Pointer to the mesh associated with this component.
     */
    Mesh* mMesh;

    /**
     * @brief Index of the texture to be used for rendering.
     */
    size_t mTextureIndex;

    /**
     * @brief Visibility flag for the mesh component.
     */
    bool mVisible = true;

    /**
     * @brief Flag indicating whether tessellation is enabled.
     */
    bool mUseTessellation = false;

    /**
     * @brief Scale factor for displacement mapping.
     */
    float mDisplacementScale = 1.0f;

    /**
     * @brief Level of tessellation to be applied.
     */
    int mTessellationLevel = 1;

    /**
     * @brief Tiling factor for texture mapping.
     */
    Vec2 mTiling = Vec2(1.0f, 1.0f);

    /**
     * @brief Time variable used for animations or effects.
     */
    float mTime = 0.0f;

public:
    /**
     * @brief Constructs a MeshComponent and initializes rendering properties.
     * @param pOwner Pointer to the owning Actor.
     */
    MeshComponent(Actor* pOwner);

    /**
     * @brief Destructor for MeshComponent.
     */
    virtual ~MeshComponent();

    /**
     * @brief Draws the mesh using the specified view-projection matrix.
     * @param viewProj The view-projection matrix.
     */
    virtual void Draw(Matrix4Row viewProj);

    // Getter and Setter methods

    /**
     * @brief Sets the mesh to be rendered by this component.
     * @param mesh Reference to the mesh object.
     */
    virtual void SetMesh(Mesh& mesh);

    /**
     * @brief Sets the index of the texture to be used for rendering.
     * @param pTextureIndex Index of the texture.
     */
    void SetTextureIndex(size_t pTextureIndex);

    /**
     * @brief Adds a texture to the mesh associated with this component.
     * @param pTexture Reference to the texture object.
     */
    void AddTexture(Texture& pTexture);

    /**
     * @brief Sets the visibility of the mesh component.
     * @param pVisible True to make the component visible, false otherwise.
     */
    void SetVisible(bool pVisible);

    /**
     * @brief Gets the visibility status of the mesh component.
     * @return True if visible, false otherwise.
     */
    bool GetVisible() const
    {
        return mVisible;
    }

    /**
     * @brief Gets the mesh associated with this component.
     * @return Pointer to the mesh object.
     */
    Mesh* GetMesh() const
    {
        return mMesh;
    }

    /**
     * @brief Enables or disables tessellation for rendering.
     * @param pUseTessellation True to enable tessellation, false to disable.
     */
    void SetUseTessellation(bool pUseTessellation)
    {
        mUseTessellation = pUseTessellation;
    }

    /**
     * @brief Sets the scale factor for displacement mapping.
     * @param pDisplacementScale Scale factor for displacement.
     */
    void SetDisplacementScale(float pDisplacementScale)
    {
        mDisplacementScale = pDisplacementScale;
    }

    /**
     * @brief Sets the level of tessellation to be applied.
     * @param pTessellationLevel Level of tessellation.
     */
    void SetTessellationLevel(int pTessellationLevel)
    {
        mTessellationLevel = pTessellationLevel;
    }

    /**
     * @brief Sets the tiling factor for texture mapping.
     * @param pTiling Tiling factor as a Vec2 object.
     */
    void SetTiling(const Vec2& pTiling)
    {
        mTiling = pTiling;
    }
};
