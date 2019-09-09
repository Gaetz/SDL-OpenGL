#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <memory>

#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "maths.h"
#include "color.h"

// A renderer class able to draw OpenGL sprites.
// It uses a specialized shader.
class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();

	void drawSprite(const Texture2D& texture, Vector2 position,
		Vector2 size = Vector2(10, 10), GLfloat rotate = 0.0f,
		Color color = Color());

private:
	Shader shader;
	std::unique_ptr<VertexArray> vertexArray;
};

#endif