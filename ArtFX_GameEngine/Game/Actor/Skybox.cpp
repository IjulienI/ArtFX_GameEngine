#include "Skybox.h"

#include "Core/Render/Asset.h"
#include "Core/Render/Component/MeshComponent.h"

Skybox::Skybox() : Actor()
{
    Asset::LoadMesh("Box.obj", "Skybox");
    Asset::LoadTexture(mScene->GetRenderer(), "Resources/Textures/Skybox/Basic.png", "Skybox");
    
    SetScale(Vec3(1000.0f, 1000.0f, 1000.0f));
    Rotate(Vec3(45.0f, 0.0f, 0.0f));
    
    Skybox::Start();
}

void Skybox::Start()
{    
    MeshComponent* skyboxMeshComponent = new MeshComponent(this);    
    skyboxMeshComponent->SetMesh(Asset::GetMesh("Skybox"));
    skyboxMeshComponent->AddTexture(Asset::GetTexture("Skybox"));
}
