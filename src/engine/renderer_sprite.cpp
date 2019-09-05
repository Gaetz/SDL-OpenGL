#include "renderer_sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "math.h"

/*static GLfloat vertexBuffer[] = {
	-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, // top left
	 0.5f, 0.5f, 0.0f,  1.0f, 1.0f, // top right
	 0.5f,-0.5f, 0.0f,  1.0f, 0.0f,// bottom right
	-0.5f,-0.5f, 0.0f,  0.0f, 0.0f // bottom left
};

static GLuint indexBuffer[] = {
	0, 1, 2, // first Triangle
	2, 3, 0  // second Triangle
};
*/

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

void SpriteRenderer::drawSprite(const Texture2D& texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	shader.use();
	/*glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));*/

    Matrix4 scaleMat = Matrix4::CreateScale(
                static_cast<float>(texture.width),
                static_cast<float>(texture.height),
                1.0f);

    Matrix4 mWorldTransform = Matrix4::CreateScale(Vector3(size.x, size.y, 1));
	mWorldTransform *= Matrix4::CreateRotationZ(rotate);
	mWorldTransform *= Matrix4::CreateTranslation(Vector3(position.x, position.y, 0.0f));

    Matrix4 model = /*scaleMat **/ mWorldTransform;

	shader.setMatrix4("model", model);
	shader.setVector3f("spriteColor", color);
/*
GLuint sampler=0;
glGenSamplers(1, &sampler);
glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
const int texUnit=0;
GLuint samplerUniform = glGetUniformLocation(shader.id, "image");
glUniform1i(samplerUniform, texUnit);
glUseProgram(0);*/
	vertexArray->setActive();
	glActiveTexture(GL_TEXTURE0);
	texture.setActive();
//glBindSampler(texUnit, sampler);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


