#ifndef GEOMETRY_RENDERER_H
#define GEOMETRY_RENDERER_H

#include "shader.h"

class GeometryRenderer
{
public:
	GeometryRenderer(const Shader &shader);
	~GeometryRenderer();

	void drawRect(glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10),
		GLfloat rotate = 0.0f,
		glm::vec4 color = glm::vec4(1.0f));

private:
	Shader shader;
	GLuint VBO, VAO, EBO;

	void initRenderData();
};

#endif