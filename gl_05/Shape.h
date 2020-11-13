#pragma once
#include "Object.h"
#include <vector>
#include <GL/glew.h>

class Shape : public Object
{
public:
	bool rotatable_;
	glm::vec4 color_;
	glm::vec3 size_;
	glm::vec3 rotation_;
	glm::vec3 scale_factor_;
	glm::mat4 model_;


	std::vector<GLfloat> verticies_;
	std::vector<GLfloat> indicies_;
	GLuint VAO_, VBO_, EBO_;

	GLuint texture_;

	Shape();
	~Shape();
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle) override;
	void scale(const glm::vec3& factor) override;
	bool isRotatable();

};

