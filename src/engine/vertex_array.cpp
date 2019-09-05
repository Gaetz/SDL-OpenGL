#include "vertex_array.h"
#include <GL/glew.h>

/*
VertexArray::VertexArray(
    const GLfloat *vertices, GLuint nbVertices,
    const GLuint *indices, GLuint nbIndices)
    : nbVertices(nbVertices), nbIndices(nbIndices)
*/

VertexArray::VertexArray(
    const std::array<GLfloat, 18> & vertexBuffer,
    const std::array<GLfloat, 12> & texBuffer
)
: id(0), vertexBufferId(0), texBufferId(0)
{
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(GLfloat), &vertexBuffer, GL_STATIC_DRAW);

    glGenBuffers(1, &texBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, texBufferId);
    glBufferData(GL_ARRAY_BUFFER, texBuffer.size() * sizeof(GLfloat), &texBuffer, GL_STATIC_DRAW);

    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    int dimensions = 2; // 2d data for texture coords
    glBindBuffer(GL_ARRAY_BUFFER, texBufferId);
    glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /*
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
    */
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &texBufferId);
    glDeleteVertexArrays(1, &id);
}

void VertexArray::setActive()
{
    glBindVertexArray(id);
}
