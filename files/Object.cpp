#include "Object.h"

void Object::move(const glm::vec3& displacement)
{
	position_ += displacement;
}

void Object::rotate(const glm::vec3& angle, const glm::vec3& point)
{
	glPushMatrix();
	glm::mat4 rotation;
	rotation = glm::translate(rotation, point);
	rotation = glm::rotate(rotation, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = translate(rotation, -point);
	rotation_matrix_ = rotation * rotation_matrix_;
	glPopMatrix();
}

void Object::rotate(const glm::vec3& angle)
{
	/*glPushMatrix();
	glm::mat4 rotation;
	rotation = glm::rotate(rotation, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation_matrix_ = rotation_matrix_* rotation;
	glPopMatrix();*/
	if (parent_ != nullptr)
		this->rotate(angle, parent_->position_ + position_ );
	else
		this->rotate(angle, position_);
}

void Object::setPosition(const glm::vec3& position)
{
	position_ = position;
}
