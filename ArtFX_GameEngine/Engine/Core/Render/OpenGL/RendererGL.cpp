#include "RendererGL.h"

#include <glew.h>
#include <SDL_image.h>

#include "Core/Class/Actor/Actor.h"
#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"
#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"

RendererGL::RendererGL() : mWindow(nullptr), mSpriteVAO(nullptr), mContext(nullptr),
mSpriteViewProj(Matrix4Row::CreateSimpleViewProj(Window::Dimensions.x, Window::Dimensions.y)),
mView(Matrix4Row::CreateLookAt(Vec3(0,0,5), Vec3::unitX, Vec3::unitZ)),
mProj(Matrix4Row::CreatePerspectiveFOV(70.0f, mWindow->GetDimensions().x , mWindow->GetDimensions().y, 0.01f, 100000.0f))
{
}

RendererGL::~RendererGL()
{
}

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
    
    return true;
}

void RendererGL::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererGL::Draw()
{
    DrawMeshes();
    DrawSprites();
}

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

void RendererGL::DrawMeshes()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    for (MeshComponent* mesh : mMeshes)
    {
        mesh->Draw(mView * mProj);
    }
}

void RendererGL::AddMesh(MeshComponent* mesh)
{
    mMeshes.emplace_back(mesh);
}

void RendererGL::RemoveMesh(MeshComponent* mesh)
{
    std::vector<MeshComponent*>::iterator it;
    it = std::find(mMeshes.begin(), mMeshes.end(), mesh);
    mMeshes.erase(it);
}

void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSldWindow());
}

void RendererGL::DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation)
{
    mSpriteShaderProgram.Use();
    Matrix4Row scaleMat = Matrix4Row::CreateScale(
    static_cast<float>(tex.GetWidht()),
    static_cast<float>(tex.GetHeight()),
    1.0f);
    Matrix4Row world = scaleMat * actor.GetTransform().GetWorldTransform();
    mSpriteShaderProgram.setMatrix4Row("uWorldTransform", world);
    tex.SetActive();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

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

void RendererGL::RemoveSprite(SpriteComponent* sprite)
{
    std::vector<SpriteComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(sc);
}

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

void RendererGL::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mSpriteVAO;
}

void RendererGL::SetSpriteShaderProgram(ShaderProgram* shaderProgram)
{
    mSpriteShaderProgram = *shaderProgram;
    mSpriteShaderProgram.Use();
}

void RendererGL::SetViewMatrix(Matrix4Row matrix)
{
    mView = matrix;
}
    
IRenderer::RendererType RendererGL::GetType()
{
    return RendererType::OPENGL;
}
