#include "Shape.h"

Shape::Shape() {}

Shape::~Shape() {}

void Shape::move(const glm::vec3& displacement)
{
	this->position += displacement;
}
void Shape::rotate(const glm::vec3& angle)
{
	this->rotation += rotation;
}
void Shape::scale(const glm::vec3& factor)
{
	this->scale_factor += factor;
}