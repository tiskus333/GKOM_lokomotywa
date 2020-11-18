#pragma once
#include "Object.h"
#include "Shape.h"
#include <memory>

class Composite : public Object
{
protected:
	std::vector<std::unique_ptr<Shape>> elements;
	const std::shared_ptr<Shader> shader_;
public:
	Shape* parent_ = nullptr;
	Composite(const glm::vec3& positon);
	~Composite();
	void draw();
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle, const glm::vec3& point) override;
	void addElement( Shape& object);
	void removeElement(uint32_t index);
	std::unique_ptr<Shape>& getElement(int index);

};

