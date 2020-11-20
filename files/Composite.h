#pragma once
#include "Object.h"
#include "Shape.h"
#include <memory>

class Composite : public Object
{
protected:
	std::vector<std::unique_ptr<Shape>> elements;
	bool rotatable_;
public:
	Composite(const glm::vec3& positon, bool rotatable = true);
	~Composite();
	void draw();
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle, const glm::vec3& point = glm::vec3(0, 0, 0)) override;
	void addElement( Shape& object);
	void removeElement(uint32_t index);
	std::unique_ptr<Shape>& getElement(int index);
	bool isRotatable();

};

