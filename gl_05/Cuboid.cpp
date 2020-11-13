#include "Cuboid.h"

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, glm::vec4 color) : size_(size)
{
	this->position_ = position;
	this->color_ = color;
}

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, GLuint texture)
{
	this->position_ = position;
	this->texture_ = texture;
}
