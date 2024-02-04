#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>
#include <array>

// Represent a Vertex Array Object
class VertexArray {
public:
    VertexArray(
            const std::array<GLfloat, 18>& vertexBuffer,
            const std::array<GLfloat, 12>& texBuffer
    );

    virtual ~VertexArray();

    void setActive() const;

private:
    GLuint id { 0 };
    GLuint vertexBufferId { 0 };
    GLuint texBufferId { 0 };
};

#endif