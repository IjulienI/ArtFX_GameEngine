#include "VertexArray.h"

#include <glew.h>

VertexArray::VertexArray(const float* vertices, unsigned int verticeCount, const unsigned int* indices,
    unsigned int indexCount) : verticeCount(verticeCount), indexCount(indexCount), vertexArrayId(0),
vertexBufferId(0), indexBufferId(0)
{
    //Generate VAO
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    //Generate VBO
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, verticeCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    //Generate Index Buffer
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(float), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &indexBufferId);
    glDeleteBuffers(1, &vertexArrayId);

}

void VertexArray::SetActive()
{
    glBindVertexArray(vertexArrayId);
}
