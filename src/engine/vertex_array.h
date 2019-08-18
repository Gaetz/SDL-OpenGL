#ifndef VEXTEX_ARRAY_H
#define VEXTEX_ARRAY_H

#include <GL/glew.h>

// Represent a Vertex Array Object
class VertexArray
{
public:
    VertexArray(const GLfloat *vertices, GLuint nbVertices,
                const GLuint *indices, GLuint nbIndices);
    virtual ~VertexArray();

    void setActive();

    inline GLuint getNbVertices() const { return nbVertices; }
    inline GLuint getNbIndices() const { return nbIndices; }

private:
    GLuint nbVertices;
    GLuint nbIndices;

    GLuint id;
    GLuint vertexBufferId;
    GLuint indexBufferId;
};

#endif