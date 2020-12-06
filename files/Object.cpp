#include "Object.h"

void Object::move(const glm::vec3& displacement)
{
	position_ += displacement;
}

void Object::rotate(const glm::vec3& angle, const glm::vec3& point)
{
	glPushMatrix();
	dynamic_rotation_matrix_ = glm::translate(dynamic_rotation_matrix_, point);
	dynamic_rotation_matrix_ = glm::rotate(dynamic_rotation_matrix_, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	dynamic_rotation_matrix_ = glm::rotate(dynamic_rotation_matrix_, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	dynamic_rotation_matrix_ = glm::rotate(dynamic_rotation_matrix_, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	dynamic_rotation_matrix_ = translate(dynamic_rotation_matrix_, -point);
	glPopMatrix();
}

void Object::rotate(const glm::vec3& angle)
{
	glPushMatrix();
	glm::mat4 rotation;
	rotation = glm::rotate(rotation, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	static_rotation_matrix_ =   rotation * static_rotation_matrix_;
	glPopMatrix();
}

void Object::setPosition(const glm::vec3& position)
{
	position_ = position;
}
