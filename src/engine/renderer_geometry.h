#ifndef GEOMETRY_RENDERER_H
#define GEOMETRY_RENDERER_H

#include <memory>

#include "shader.h"
#include "vertex_array.h"
#include "color.h"

// A renderer class able to draw OpenGL rectangles.
// It uses a specialized shader.
class GeometryRenderer
{
public:
	GeometryRenderer(const Shader &shader);
	~GeometryRenderer();

	void drawRect(Vector2 position,
				  Vector2 size = Vector2(10, 10),
				  GLfloat rotate = 0.0f,
				  Color color = Color());

private:
	Shader shader;
	std::unique_ptr<VertexArray> vertexArray;
};

#endif