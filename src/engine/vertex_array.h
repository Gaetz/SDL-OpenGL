#ifndef VEXTEX_ARRAY_H
#define VEXTEX_ARRAY_H

#include <GL/glew.h>
#include <array>

// Represent a Vertex Array Object
class VertexArray
{
public:
    /*VertexArray(const GLfloat *vertices, GLuint nbVertices,
                const GLuint *indices, GLuint nbIndices);*/

    VertexArray(
        const std::array<GLfloat, 18> & vertexBuffer,
        const std::array<GLfloat, 12> & texBuffer
    );
    virtual ~VertexArray();

    void setActive();

    //inline GLuint getNbVertices() const { return nbVertices; }
    //inline GLuint getNbIndices() const { return nbIndices; }

private:
    //GLuint nbVertices;
    //GLuint nbIndices;

    GLuint id;
    GLuint vertexBufferId;
    GLuint texBufferId;
};

#endif