#pragma once
#include "Object.h"
#include "Shader.h"
#include "shprogram.h"
#include <vector>


class Shape : public Object
{
public:
	glm::vec3 color_;
	glm::vec3 size_;
	glm::mat4 model_;
	ShaderProgram shader_;


	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;
	GLuint VAO_, VBO_, EBO_;

	std::string texture_path_;
	Shape(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path);
	~Shape();
	void bindBuffers();
	void freeBuffers();
	void draw(const glm::mat4& parent_model = glm::mat4(1.f));
	void scale(const glm::vec3& factor);
	void setSize(const glm::vec3& size);
	void setColor(const float r, const float g, const float b);
	void setColor(const uint32_t r, uint32_t g, const uint32_t b);


};

