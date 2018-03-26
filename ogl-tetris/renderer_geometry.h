#pragma once
#ifndef _GEOMETRY_RENDERER_
#define _GEOMETRY_RENDERER_

#include "shader.h"

class GeometryRenderer
{
public:
	GeometryRenderer(Shader &shader);
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