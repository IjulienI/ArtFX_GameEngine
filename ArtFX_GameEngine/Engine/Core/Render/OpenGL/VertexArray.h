#pragma once

constexpr float vertices[] = {
    -0.5f,  0.5f,  0.0f,	//A
    0.5f ,  0.5f,  0.0f,	//B
    0.5f , -0.5f,  0.0f,	//C
    -0.5f, -0.5f,  0.0f};   //D     

constexpr unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
    };


class VertexArray
{
private:
    unsigned int verticeCount;
    unsigned int indexCount;

    unsigned int vertexArrayId;
    unsigned int vertexBufferId;
    unsigned int indexBufferId;
    
public:
    VertexArray(const float* vertices, unsigned int verticeCount, const unsigned int* indices, unsigned int indexCount);
    ~VertexArray();

    void SetActive();
    unsigned int GetVerticeCount() const { return verticeCount; }
    unsigned int GetIndicesCount() const { return indexCount; }
};
