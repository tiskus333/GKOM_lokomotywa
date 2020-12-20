#include "Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>



Shape::Shape(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path)
{
	this->position_ = position;
	this->size_ = size;
	this->color_ = color;
	this->texture_path_ = texture_path;
}

Shape::~Shape() {
	freeBuffers();
}

void Shape::bindBuffers()
{
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void Shape::freeBuffers()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
}

void Shape::draw(const glm::mat4& parent_model)
{
	glPushMatrix();
	model_ = parent_model * glm::translate(dynamic_rotation_matrix_, position_) * static_rotation_matrix_;
	model_ = glm::scale(model_, size_);

	GLuint transformLoc = glGetUniformLocation(shader_.get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_));
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPopMatrix();
}

void Shape::scale(const glm::vec3& factor)
{
	this->size_ *= factor;
}
void Shape::setSize(const glm::vec3& size)
{
	this->size_ = size;
}

void Shape::setColor(const float r, const float g, const float b)
{
	this->color_ = glm::vec3(r, g, b);
}

void Shape::setColor(const uint32_t r, uint32_t g, const uint32_t b)
{
	this->setColor(r / 255.0f, g / 255.0f, b / 255.0f);
}

