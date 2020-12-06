#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class Object
{
public:
	Object* parent_ = nullptr;
	glm::vec3 position_;
	glm::mat4 static_rotation_matrix_;
	glm::mat4 dynamic_rotation_matrix_;

	void move(const glm::vec3& displacement);
	void rotate(const glm::vec3& angle, const glm::vec3& point);
	void rotate(const glm::vec3& angle);
	void setPosition(const glm::vec3& position);
};

