#include "Composite.h"

Composite::Composite(const glm::vec3& positon)
{
	this->position_ = position_;
}

Composite::~Composite()
{
}

void Composite::draw()
{
	for (auto& el : elements)
		el->draw();
}

void Composite::move(const glm::vec3& displacement)
{
	for (const auto& element : elements)
		element->move(displacement);
}

void Composite::rotate(const glm::vec3& angle, const glm::vec3& point = glm::vec3(0, 0, 0))
{
	for (const auto& element : elements)
		element->rotate(angle, point);
}

void Composite::addElement( Shape& shape)
{
	elements.push_back(std::make_unique<Shape>(shape));
}

void Composite::removeElement(uint32_t index)
{
	if (index >= 0 || index < elements.size())
	{
		//elements.at(index).reset();
		elements.erase(elements.begin() + index);
	}
}

std::unique_ptr<Shape>& Composite::getElement(int index)
{
	return elements.at(index);
}

bool Composite::isRotatable()
{
	return rotatable_;
}
