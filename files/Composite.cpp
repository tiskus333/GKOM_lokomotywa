#include "Composite.h"

Composite::Composite()
{
}

void Composite::draw()
{
}

void Composite::move(const glm::vec3& displacement)
{
}

void Composite::rotate(const glm::vec3& angle)
{
}

void Composite::scale(const glm::vec3& factor)
{
}

void Composite::addElement()
{
}

void Composite::removeElement(int index)
{
}

std::unique_ptr<Object>& Composite::getElement(int index)
{
	return elements.at(index);
}
