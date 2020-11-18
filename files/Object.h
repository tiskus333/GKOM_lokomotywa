#pragma once
#include <glm/glm.hpp>

class Object
{
public:
	glm::vec3 position_;
	glm::vec3 rotation_;

	virtual void move(const glm::vec3& displacement) = 0;
	virtual void rotate(const glm::vec3& angle, const glm::vec3& point) = 0;

};

