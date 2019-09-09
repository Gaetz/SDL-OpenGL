#include "renderer_sprite.h"

static std::array<GLfloat, 18> vertexBuffer = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

static std::array<GLfloat, 12> texBuffer = {
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

SpriteRenderer::SpriteRenderer(const Shader& shader): shader(shader)
{
	vertexArray = std::make_unique<VertexArray>(vertexBuffer, texBuffer);
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::drawSprite(const Texture2D& texture, Vector2 position,
	Vector2 size, GLfloat rotate, Color color)
{
	shader.use();

    Matrix4 scaleMat = Matrix4::createScale(
                static_cast<float>(texture.width),
                static_cast<float>(texture.height),
                1.0f);

    Matrix4 mWorldTransform = Matrix4::createScale(Vector3(size.x, size.y, 1));
	mWorldTransform *= Matrix4::createRotationZ(rotate);
	mWorldTransform *= Matrix4::createTranslation(Vector3(position.x + size.x / 2, position.y + size.y / 2, 0.0f));

    Matrix4 model = mWorldTransform;

	shader.setMatrix4("model", model);
	shader.setVector3f("spriteColor", color.toVector3());

	vertexArray->setActive();
	texture.setActive();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}


