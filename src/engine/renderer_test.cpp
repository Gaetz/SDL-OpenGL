#include "renderer_test.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>

#include "maths.h"


static std::array<GLfloat, 18> vertexBuffer = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

static std::array<GLfloat, 12> texcoords = {
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};


TestRenderer::TestRenderer(const Shader &shader) : 
    shader(shader)
{
    vertexArray = new VertexArray(vertexBuffer, texcoords);
    /*GLuint vertexBufferId = 0;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

    
    GLuint vt_vbo;
    glGenBuffers(1, &vt_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);


//    GLuint indexBufferId;
//    glGenBuffers(1, &indexBufferId);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GL_UNSIGNED_INT), indexBuffer, GL_STATIC_DRAW);


    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);

    int dimensions = 2; // 2d data for texture coords
    glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
    glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);
    //glBindBuffer(GL_ARRAY_BUFFER, indexBufferId);
    //glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), reinterpret_cast<void*>(sizeof(GL_FLOAT)*3));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);*/
}

TestRenderer::~TestRenderer()
{
    delete vertexArray;
}

void TestRenderer::draw(const Texture2D &texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate)
{
    shader.use();
    /*
    glm::mat4 matrix( 1.0f );
    
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));
    */

    Matrix4 scaleMat = Matrix4::CreateScale(
                static_cast<float>(texture.width),
                static_cast<float>(texture.height),
                1.0f);

    Matrix4 mWorldTransform = Matrix4::CreateScale(Vector3(size.x, size.y, 1));
	mWorldTransform *= Matrix4::CreateRotationZ(rotate);
	mWorldTransform *= Matrix4::CreateTranslation(Vector3(position.x, position.y, 0.0f));

    Matrix4 model = scaleMat * mWorldTransform;

    shader.setMatrix4("model", model);
    //glBindVertexArray(vao);
    vertexArray->setActive();

    //glActiveTexture(GL_TEXTURE0);
    texture.setActive();
    glDrawArrays(GL_TRIANGLES, 0, 6);


	//vertexArray->setActive();
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}