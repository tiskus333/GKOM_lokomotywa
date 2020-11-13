#pragma once
#include <glm/glm.hpp>

class Object
{
protected:
	glm::vec3 position_;
	Object* parent_;
	glm::vec3 rotation_;

public:
	virtual void draw() = 0;
	virtual void move(const glm::vec3& displacement) = 0;
	virtual void rotate(const glm::vec3& angle, const glm::vec3& point) = 0;
	virtual void scale(const glm::vec3& factor) = 0;
	virtual ~Object() = 0;

};

