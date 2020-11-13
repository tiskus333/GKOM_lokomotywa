#pragma once
#include <glm/glm.hpp>

class Object
{
protected:
	glm::vec3 position_;
	Object* parent_;

public:
	virtual void draw() = 0;
	virtual void move(const glm::vec3& displacement) = 0;
	virtual void rotate(const glm::vec3& angle) = 0;
	virtual void scale(const glm::vec3& factor) = 0;
	virtual ~Object() = default;

};

