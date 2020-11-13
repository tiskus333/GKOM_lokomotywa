#pragma once
#include "Object.h"
#include "Shape.h"
#include <memory>

class Composite : public Object
{
protected:
	std::vector<std::unique_ptr<Object>> elements;
public:
	Composite();
	~Composite() = default;
	void draw() override;
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle) override;
	void scale(const glm::vec3& factor) override;
	void addElement();
	void removeElement(int index);
	std::unique_ptr<Object>& getElement(int index);

};

