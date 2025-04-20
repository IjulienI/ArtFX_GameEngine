#include "VertexArray.h"

#include <glew.h>

VertexArray::VertexArray(const float* vertices, unsigned int verticeCount) : verticeCount(verticeCount), indexCount(indexCount), vertexArrayId(0),
vertexBufferId(0), indexBufferId(0)
{
    //Generate VAO
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    //Generate VBO
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, verticeCount * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

    //Pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //TexCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
