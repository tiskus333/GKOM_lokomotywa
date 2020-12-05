#include "Composite.h"

Composite::Composite(const glm::vec3& positon, bool rotatable) : rotatable_(rotatable)
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
	position_ += displacement;
	/*for (const auto& element : elements)
		element->move(displacement);*/
}

void Composite::rotate(const glm::vec3& angle, const glm::vec3& point)
{
	if (isRotatable())
	{
		this->rotation_ += angle;
		rotation_.x -= rotation_.x > 360.0f ? 360.0f : 0.0f;
		rotation_.y -= rotation_.y > 360.0f ? 360.0f : 0.0f;
		rotation_.z -= rotation_.z > 360.0f ? 360.0f : 0.0f;
	}
	//if (isRotatable())
	//	for (const auto& element : elements)
	//	{
	//		element->rotate(angle, point);
	//		//element->rotate(angle);
	//	}
}

void Composite::rotate(const glm::vec3& angle)
{
	this->rotate(angle, position_);

	//if(isRotatable())
	//	for (const auto& element : elements)
	//	{
	//		element->rotate(angle,position_);
	//		//element->rotate(angle);
	//	}
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

bool Composite::isRotatable()
{
	return rotatable_;
}
