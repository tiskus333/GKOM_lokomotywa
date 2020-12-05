#include "Object.h"

void Object::move(const glm::vec3& displacement)
{
	position_ += displacement;
}

void Object::rotate(const glm::vec3& angle, const glm::vec3& point)
{
	glPushMatrix();
	rotation_matrix_ = glm::translate(rotation_matrix_, point);
	rotation_matrix_ = glm::rotate(rotation_matrix_, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_matrix_ = glm::rotate(rotation_matrix_, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_matrix_ = glm::rotate(rotation_matrix_, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation_matrix_ = translate(rotation_matrix_, -point);
	glPopMatrix();
}

void Object::rotate(const glm::vec3& angle)
{
	this->rotate(angle, position_);
}

void Object::setPosition(const glm::vec3& position)
{
	position_ = position;
}
