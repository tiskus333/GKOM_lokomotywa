#include "Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Shape::Shape(): rotatable_(false), color_(0.0f,0.0f,0.0f), size_(1), scale_factor_(1)   {
	//this->bindBuffers();
}

Shape::~Shape() {
	this->freeBuffers();
}

void Shape::bindBuffers()
{
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO_);
	//static_cast<void*>(&vertices)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(7 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void Shape::freeBuffers()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
}

void Shape::draw()
{
	//const std::shared_ptr<Shader> shader
	//glm::mat4 model = glm::scale(glm::mat4(1.0f), size_);

	glm::mat4 model(1.0f);
	if(parent_ != nullptr)
	model = translate(model, parent_->position_);
	else
	model = translate(model, position_);
	model = glm::rotate(model, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, size_);

	//texture_.useTexture(shader);
	//shader->setTransformMatrix("model", model);
	GLuint transformLoc = glGetUniformLocation(shader_->get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Shape::move(const glm::vec3& displacement)
{
	this->position_ += displacement;
}
void Shape::rotate(const glm::vec3& angle, const glm::vec3& point = glm::vec3(0.0f,0.0f,0.0f))
{
	//if(isRotatable())
		this->rotation_ += angle;
}
void Shape::scale(const glm::vec3& factor)
{
	this->scale_factor_ += factor;
}

bool Shape::isRotatable()
{
	return rotatable_;
}
