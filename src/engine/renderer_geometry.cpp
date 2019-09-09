#include "renderer_geometry.h"
#include "maths.h"

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

GeometryRenderer::GeometryRenderer(const Shader &shader): shader(shader)
{
	vertexArray = std::make_unique<VertexArray>(vertexBuffer, texBuffer);
}

GeometryRenderer::~GeometryRenderer()
{
}

void GeometryRenderer::drawRect(Vector2 position, Vector2 size, GLfloat rotate, Color color)
{
	shader.use();

    Matrix4 mWorldTransform = Matrix4::createScale(Vector3(size.x, size.y, 1));
	mWorldTransform *= Matrix4::createRotationZ(rotate);
	mWorldTransform *= Matrix4::createTranslation(Vector3(position.x + size.x / 2, position.y, 0.0f));

    Matrix4 model = mWorldTransform;
	shader.setMatrix4("model", model);
	shader.setVector4f("vertexColor", color.toVector4());

	vertexArray->setActive();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
