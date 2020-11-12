#pragma once
#include "Object.h"
#include <vector>
#include <GL/glew.h>

class Shape : public Object
{
public:
	bool rotatable;
	glm::vec3 color;
	glm::vec3 size;
	glm::vec3 rotation;
	glm::vec3 scale_factor;
	glm::mat4 model;


	std::vector<GLfloat> verticies;
	std::vector<GLfloat> indicies;
	GLuint VAO, VBO, EBO;

	const char* texture_path;

	Shape();
	~Shape();
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle) override;
	void scale(const glm::vec3& factor) override;

};

