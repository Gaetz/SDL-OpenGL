#ifndef VEXTEX_ARRAY_H
#define VEXTEX_ARRAY_H

// Represent a Vertex Array Object
class VertexArray
{
public:
    VertexArray(const float *vertices, unsigned int nbVertices,
                const unsigned int *indices, unsigned int nbIndices);
    virtual ~VertexArray();

    void setActive();

    inline unsigned int getNbVertices() const { return nbVertices; }
    inline unsigned int getNbIndices() const { return nbIndices; }

private:
    unsigned int nbVertices;
    unsigned int nbIndices;

    unsigned int id;
    unsigned int vertexBufferId;
    unsigned int indexBufferId;
};

#endif