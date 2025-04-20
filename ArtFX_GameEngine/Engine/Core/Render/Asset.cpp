#include "Asset.h"

#include <sstream>

#include "RendererSdl.h"
#include "Debug/Log.h"
#include "tiny_obj_loader.h"


std::map<std::string, Texture> Asset::mTextures = {};
std::map<std::string, Mesh> Asset::mMeshes = {};

Texture Asset::LoadTexture(IRenderer& renderer, const std::string& filePath, const std::string& name)
{
    mTextures[name] = LoadTextureFromFile(renderer, filePath);
    return mTextures[name];
}

Texture& Asset::GetTexture(const std::string& name)
{
    if(mTextures.find(name) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture "<<name<<" does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[name];
}

Mesh Asset::LoadMesh(const std::string& pFileName, const std::string& pName)
{
    mMeshes[pName] = LoadMeshFromFile(pFileName);
    return mMeshes[pName];
}

Mesh& Asset::GetMesh(const std::string& pName)
{
    if (mMeshes.count(pName) == 0)
    {
        Log::Error(LogType::Application, "No mesh with name '" + pName + "'");
    }
    return mMeshes[pName];
}

void Asset::Clear()
{
    for(auto iter : mTextures)
    {
        iter.second.unload();
    }
    mTextures.clear();
}

Texture Asset::LoadTextureFromFile(IRenderer& renderer, const std::string& filePath)
{
    Texture texture;
    texture.LoadTexture(renderer, filePath);
    return texture;
}

Mesh Asset::LoadMeshFromFile(const std::string& pFileName)
{
    Mesh loaded;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err, warn;
    std::string directory = "Resources/Meshes/";
    bool succes = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, (directory + pFileName).c_str(), directory.c_str());
    if (!succes)
    {
        Log::Error(LogType::Error, "Mesh + " + pFileName + " could not be loaded");
        return Mesh();
    }
    else
    {
        Log::Info("Mesh " + pFileName + " loaded");
    }
    std::vector<Vertex> vertices;
    for (int i = 0; i < shapes.size(); i++)
    {
        tinyobj::shape_t &shape = shapes[i];
        tinyobj::mesh_t &mesh = shape.mesh;
        for (int j = 0; j < mesh.indices.size(); j++)
        {
            tinyobj::index_t i = mesh.indices[j];
            Vec3 pos = Vec3
            {
                attrib.vertices[i.vertex_index * 3],
                attrib.vertices[i.vertex_index * 3 + 1],
                attrib.vertices[i.vertex_index * 3 + 2]
            };
            Vec3 normal = Vec3
            {
                attrib.normals[i.normal_index * 3],
                attrib.normals[i.normal_index * 3 + 1],
                attrib.normals[i.normal_index * 3 + 2]
            };
            Vec2 texCoord = Vec2
            {
                attrib.texcoords[i.texcoord_index * 2],
                attrib.texcoords[i.texcoord_index * 2 + 1]
            };
            Vertex vert = {pos, normal, texCoord};
            vertices.push_back(vert);
        }
    }
    return Mesh(vertices);
}
