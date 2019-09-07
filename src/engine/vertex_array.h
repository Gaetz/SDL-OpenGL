#ifndef VEXTEX_ARRAY_H
#define VEXTEX_ARRAY_H

#include <GL/glew.h>
#include <array>

// Represent a Vertex Array Object
class VertexArray
{
public:
    VertexArray(
        const std::array<GLfloat, 18> & vertexBuffer,
        const std::array<GLfloat, 12> & texBuffer
    );
    virtual ~VertexArray();

    void setActive();

private:
    GLuint id;
    GLuint vertexBufferId;
    GLuint texBufferId;
};

#endif