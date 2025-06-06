/**
 * @file RendererGL.cpp
 * @brief Implementation of the RendererGL class, which provides OpenGL-based rendering functionality.
 */

#include "RendererGL.h"

#include <glew.h>
#include <SDL_image.h>

#include "Core/Class/Actor/Actor.h"
#include "Core/Physic/Component/BaseCollisionComponent.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"

/**
 * @brief Constructs a RendererGL object and initializes rendering matrices.
 */
RendererGL::RendererGL() : mWindow(nullptr), mSpriteVAO(nullptr), mContext(nullptr),
mSpriteViewProj(Matrix4Row::CreateSimpleViewProj(Window::Dimensions.x, Window::Dimensions.y)),
mView(Matrix4Row::CreateLookAt(Vec3(0,0,5), Vec3::unitX, Vec3::unitZ)),
mProj(Matrix4Row::CreatePerspectiveFOV(0.8f, mWindow->GetDimensions().x , mWindow->GetDimensions().y, 0.01f, 10000.0f))
{
    mDrawType = DrawType::Unlit;
    mSpriteViewProj = Matrix4Row::CreateSimpleViewProj(800.0f, 600.0f);
}

RendererGL::~RendererGL()
{
}

/**
 * @brief Initializes the OpenGL renderer with the given window.
 * @param rWindow Reference to the window object.
 * @return True if initialization succeeded, false otherwise.
 */
bool RendererGL::Initialize(Window& rWindow)
{
    mWindow = &rWindow;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //8 bits color buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    mContext = SDL_GL_CreateContext(mWindow->GetSldWindow());
    glewExperimental = GL_TRUE;
    if(glewInit()!= GLEW_OK)
    {
        Log::Error(LogType::Video, "Failed to initialize GLEW");
        return false;
    }
    glGetError();

    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Failed to initialize SDL_Image");
    }
    mSpriteVertexShader.Load("SpriteShader.vert", ShaderType::VERTEX);
    mSpriteFragmentShader.Load("SpriteShader.frag", ShaderType::FRAGMENT);
    mSpriteShaderProgram.Compose({
        &mSpriteVertexShader,
        &mSpriteFragmentShader
    });
    mSpriteVAO = new VertexArray(spriteVertices, 4);
    mSpriteViewProj = Matrix4Row::CreateSimpleViewProj(Window::Dimensions.x, Window::Dimensions.y);
    
    return true;
}

/**
 * @brief Begins the drawing process by clearing the screen.T
 */
void RendererGL::BeginDraw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Draws all registered objects based on the current draw type.
 */
void RendererGL::Draw()
{
    switch (mDrawType)
    {
    case DrawType::Unlit:        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        DrawMeshes();
        DrawSprites();
        break;
    case DrawType::Debug:        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        DrawMeshes();
        DrawSprites();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        DrawCollisions();
        break;
    case DrawType::Wireframe:
        glLineWidth(0.5f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        DrawMeshes();
        DrawSprites();
        break;
    case DrawType::Collision:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        DrawCollisions();
        break;
    }
}

/**
 * @brief Draws all registered sprite components.
 */
void RendererGL::DrawSprites()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteShaderProgram.Use();
    mSpriteShaderProgram.setMatrix4Row("uViewProj", mSpriteViewProj);
    mSpriteVAO->SetActive();

    for (SpriteComponent* sprite : mSprites)
    {
        sprite->Draw(*this);
    }
}

/**
 * @brief Draws all registered mesh components.
 */
void RendererGL::DrawMeshes()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    for (MeshComponent* mesh : mMeshes)
    {
        if (mesh->GetVisible())
            mesh->Draw(mView * mProj);
    }
}

/**
 * @brief Draws all registered collision components.
 */
void RendererGL::DrawCollisions()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    for (BaseCollisionComponent* collision : mCollisions)
    {
        collision->Draw(mView * mProj);
    }
}

/**
 * @brief Adds a mesh component to the renderer.
 * @param mesh Pointer to the mesh component.
 */
void RendererGL::AddMesh(MeshComponent* mesh)
{
    mMeshes.emplace_back(mesh);
}

/**
 * @brief Removes a mesh component from the renderer.
 * @param mesh Pointer to the mesh component.
 */
void RendererGL::RemoveMesh(MeshComponent* mesh)
{
    std::vector<MeshComponent*>::iterator it;
    it = std::find(mMeshes.begin(), mMeshes.end(), mesh);
    mMeshes.erase(it);
}

/**
 * @brief Adds a collision component to the renderer.
 * @param collision Pointer to the collision component.
 */
void RendererGL::AddCollision(BaseCollisionComponent* collision)
{
    mCollisions.emplace_back(collision);
}

/**
 * @brief Removes a collision component from the renderer.
 * @param collision Pointer to the collision component.
 */
void RendererGL::RemoveCollision(BaseCollisionComponent* collision)
{
    std::vector<BaseCollisionComponent*>::iterator it;
    it = std::find(mCollisions.begin(), mCollisions.end(), collision);
    mCollisions.erase(it);
}

/**
 * @brief Ends the drawing process and swaps the window buffers.
 */
void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSldWindow());
}

/**
 * @brief Draws a sprite for a given actor using the specified texture and transformation.
 * @param actor Reference to the actor.
 * @param tex Reference to the texture.
 * @param rect Source rectangle for the texture.
 * @param pos Position to draw the sprite.
 * @param orientation Flip orientation for the sprite.
 */
void RendererGL::DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation)
{
    mSpriteShaderProgram.Use();

    actor.GetTransform().ComputeWorldTransform();
    
    Matrix4Row scaleMat = Matrix4Row::CreateScale(
    static_cast<float>(tex.GetWidht()),
    static_cast<float>(tex.GetHeight()),
    0.0f);
    Matrix4Row world = scaleMat * actor.GetTransform().GetWorldTransform();
    mSpriteShaderProgram.setMatrix4Row("uWorldTransform", world);
    tex.SetActive();
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

/**
 * @brief Adds a sprite component to the renderer.
 * @param sprite Pointer to the sprite component.
 */
void RendererGL::AddSprite(SpriteComponent* sprite)
{
    int spriteDrawOrder = sprite->GetDrawOrder();
    std::vector<SpriteComponent*>::iterator sc;
    for(sc = mSprites.begin(); sc != mSprites.end(); ++sc)
    {
        if(spriteDrawOrder < (*sc)->GetDrawOrder()) break;
    }
    mSprites.insert(sc, sprite);
}

/**
 * @brief Removes a sprite component from the renderer.
 * @param sprite Pointer to the sprite component.
 */
void RendererGL::RemoveSprite(SpriteComponent* sprite)
{
    std::vector<SpriteComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(sc);
}

/**
 * @brief Toggles wireframe rendering mode.
 * @param status True to enable wireframe mode, false to disable.
 */
void RendererGL::ShowWireframe(bool status)
{
    if(status)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

/**
 * @brief Closes the renderer and releases resources.
 */
void RendererGL::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mSpriteVAO;
}

/**
 * @brief Sets the shader program for rendering sprites.
 * @param shaderProgram Pointer to the shader program.
 */
void RendererGL::SetSpriteShaderProgram(ShaderProgram* shaderProgram)
{
    mSpriteShaderProgram = *shaderProgram;
    mSpriteShaderProgram.Use();
}

/**
 * @brief Sets the view matrix for rendering.
 * @param matrix The view matrix.
 */
void RendererGL::SetViewMatrix(Matrix4Row matrix)
{
    mView = matrix;
}

/**
 * @brief Sets the draw type for rendering.
 * @param type The draw type.
 */
void RendererGL::SetDawType(DrawType type)
{
    mDrawType = type;
}

/**
 * @brief Gets the type of the renderer.
 * @return RendererType enum value.
 */
IRenderer::RendererType RendererGL::GetType()
{
    return RendererType::OPENGL;
}
