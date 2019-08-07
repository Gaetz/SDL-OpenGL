#include "renderer_geometry.h"
#include <glm/gtc/matrix_transform.hpp>

static float vertexBuffer[] = {
	-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, // top left + vertically inverted texture
	 0.5f, 0.5f, 0.0f,  1.0f, 1.0f, // top right
	 0.5f,-0.5f, 0.0f,  1.0f, 0.0f,// bottom right
	-0.5f,-0.5f, 0.0f,  0.0f, 0.0f // bottom left
};

static unsigned int indexBuffer[] = {
	0, 1, 2, // first Triangle
	2, 3, 0  // second Triangle
};

GeometryRenderer::GeometryRenderer(const Shader &shader): shader(shader)
{
	vertexArray = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

GeometryRenderer::~GeometryRenderer()
{
	delete vertexArray;
}

void GeometryRenderer::drawRect(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
	shader.use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Draw from upper left edge
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setMatrix4("model", model);
	shader.setVector4f("vertexColor", color);

	vertexArray->setActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//glBindVertexArray(0); // no need to unbind it every time
}
