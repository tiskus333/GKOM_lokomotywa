#pragma once
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

void Composite::addElement( Shape& shape)
{
	shape.parent_ = this;
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
