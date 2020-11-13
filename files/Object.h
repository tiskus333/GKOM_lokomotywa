#pragma once
#include <glm/glm.hpp>

class Object
{
protected:
	glm::vec3 position_;
	Object* parent_;
	glm::vec3 rotation_;

public:
	virtual void move(const glm::vec3& displacement) = 0;
	virtual void rotate(const glm::vec3& angle, const glm::vec3& point) = 0;

};

