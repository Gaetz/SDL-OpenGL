#include "vertex_array.h"
#include <GL/glew.h>

VertexArray::VertexArray(
    const float *vertices, unsigned int _nbVertices,
    const unsigned int *indices, unsigned int _nbIndices)
    : nbVertices(_nbVertices), nbIndices(_nbIndices)
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, nbVertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);

    // Reset buffer
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &indexBufferId);
    glDeleteVertexArrays(1, &id);
}

void VertexArray::setActive()
{
    glBindVertexArray(id);
}
