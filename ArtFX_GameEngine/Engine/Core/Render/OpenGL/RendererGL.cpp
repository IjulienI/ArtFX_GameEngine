#include "RendererGL.h"

#include <glew.h>
#include <SDL_image.h>

#include "Core/Render/Component/SpriteComponent.h"
#include "Debug/Log.h"

RendererGL::RendererGL() : mWindow(nullptr), mVao(nullptr), mContext(nullptr), mShaderProgram(nullptr)
{
}

RendererGL::~RendererGL()
{
    delete mVao;
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
    mVao = new VertexArray(vertices, 4, indices, 6);
    return true;

}

void RendererGL::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (mShaderProgram != nullptr)
    {
        mShaderProgram->Use();
    }
    mVao->SetActive();
}

void RendererGL::Draw()
{
}

void RendererGL::DrawSprites()
{
}

void RendererGL::EndDraw()
{
    SDL_GL_SwapWindow(mWindow->GetSldWindow());
}

void RendererGL::DrawSprite(Actor& actor, Texture& tex, Rectangle rect, Vec2 pos, Flip orientation)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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

void RendererGL::Close()
{
    SDL_GL_DeleteContext(mContext);
    delete mVao;
}

void RendererGL::SetShaderProgram(ShaderProgram* shaderProgram)
{
    mShaderProgram = shaderProgram;
}
    
IRenderer::RendererType RendererGL::GetType()
{
    return RendererType::OPENGL;
}
