#ifndef TEST_RENDERER_H
#define TEST_RENDERER_H

#include "shader.h"
#include "texture.h"
#include "vertex_array.h"

// A renderer class able to draw OpenGL sprites.
// It uses a specialized shader.
class TestRenderer
{
public:
	TestRenderer(const Shader& shader);
	~TestRenderer();

	void draw(const Texture2D& texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate);

private:
	Shader shader;
	GLuint vao;
	VertexArray* vertexArray;
};

#endif