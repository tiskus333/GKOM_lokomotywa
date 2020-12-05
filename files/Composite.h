#pragma once
#include "Object.h"
#include "Shape.h"
#include <memory>

class Composite : public Object
{
protected:
	std::vector<std::unique_ptr<Shape>> elements;
public:
	Composite(const glm::vec3& positon);
	~Composite();
	void draw();
	void addElement( Shape& object);
	void removeElement(uint32_t index);
	std::unique_ptr<Shape>& getElement(int index);

};

