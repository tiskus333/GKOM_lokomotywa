#include "Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>



Shape::Shape(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path, bool is_light_source)
: number_of_light_(-1)
{
	this->position_ = position;
	this->size_ = size;
	this->color_ = color;
	this->texture_path_ = texture_path;
	this->is_light_source_ = is_light_source;
	if(texture_path_ != "")
		this->texture_ = Scene::getScene().getTexture(texture_path_);
}

Shape::~Shape()
{
	freeBuffers();
	if (is_light_source_ && number_of_light_ != -1)
	{
		Scene::getScene().removePointLightSource((unsigned int)number_of_light_);
	}
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

//positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
//normal vector
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
//texture
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(9 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

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
	if (is_light_source_)
	{
		glm::vec3 placement = position_;
		if (parent_ != nullptr)
		{
			placement += parent_->position_;
		}
		if (number_of_light_ == -1)
		{
			number_of_light_ = Scene::getScene().addPointLightSource(placement, color_);
		}
		else
		{
			Scene::getScene().updatePointLightSource(number_of_light_, placement, color_);
		}
	}
	this->shader_.Use();
	bool hasTexture = texture_path_ != "";
	shader_.setBool("hasTexture", hasTexture);
	if (hasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_);
		glUniform1i(glGetUniformLocation(shader_.get_programID(), "Texture0"), 0);
	}
	glPushMatrix();
	model_ = parent_model * glm::translate(dynamic_rotation_matrix_, position_) * static_rotation_matrix_;
	model_ = glm::scale(model_, size_);

	shader_.setMatrix4fv("transform",model_);
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
	updateVerticiesColor();
	bindBuffers();
}

void Shape::setColor(const uint32_t r, uint32_t g, const uint32_t b)
{
	this->setColor(r / 255.0f, g / 255.0f, b / 255.0f);
}

void Shape::updateVerticiesColor()
{
	for (uint32_t i = 3; i < vertices_.size(); i += 11)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i + 1) = color_.y;
		vertices_.at(i + 2) = color_.z;
	}
}

void Shape::setShader(const ShaderProgram& shader) {

	shader_ = shader;
}

