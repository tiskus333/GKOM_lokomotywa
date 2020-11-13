#include "Shape.h"

Shape::Shape() {}

Shape::~Shape() {}

void Shape::draw()
{
}

void Shape::move(const glm::vec3& displacement)
{
	this->position_ += displacement;
}
void Shape::rotate(const glm::vec3& angle, const glm::vec3& point = glm::vec3(0,0,0))
{
	if(isRotatable())
		this->rotation_ += angle;
}
void Shape::scale(const glm::vec3& factor)
{
	this->scale_factor_ += factor;
}

bool Shape::isRotatable()
{
	return rotatable_;
}
