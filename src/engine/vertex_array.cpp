#include "vertex_array.h"
#include <GL/glew.h>

VertexArray::VertexArray(
    const float *vertices, unsigned int nbVertices,
    const unsigned int *indices, unsigned int nbIndices)
    : nbVertices(nbVertices), nbIndices(nbIndices)
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, nbVertices * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(sizeof(float)*3)	);

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
