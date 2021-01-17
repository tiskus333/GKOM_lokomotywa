#pragma once
#include "Composite.h"

Composite::Composite(const glm::vec3& position)
{
	this->position_ = position;
}


void Composite::draw()
{
	const glm::mat4 model = glm::translate(dynamic_rotation_matrix_, position_) * static_rotation_matrix_;
	for (auto& el : elements)
		el->draw(model);
}

void Composite::setShader(const ShaderProgram& shader)
{
	
	for (auto& el : elements)
		el->setShader(shader);
}

void Composite::addElement( Shape& shape)
{
	shape.setParent(this);
	elements.push_back(&shape);
}

void Composite::removeElement(uint32_t index)
{
	if (index >= 0 || index < elements.size())
	{
		//elements.at(index).reset();
		elements.erase(elements.begin() + index);
	}
}

Shape* Composite::getElement(int index)
{
	return index < elements.size() ? elements.at(index) : nullptr;
}
