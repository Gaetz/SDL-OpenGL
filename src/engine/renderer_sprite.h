#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <memory>

#include "shader.h"
#include "texture.h"
#include "vertex_array.h"

// A renderer class able to draw OpenGL sprites.
// It uses a specialized shader.
class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();

	void drawSprite(const Texture2D& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	std::unique_ptr<VertexArray> vertexArray;
};

#endif