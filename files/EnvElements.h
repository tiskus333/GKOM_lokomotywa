#pragma once
#include "Cacti.h"
class EnvElements
{
private:
	std::vector<Composite> cvec;
	glm::vec3 LastLocomotivePosition;
	Cacti cacti = Cacti({ 0,0,0 });

public:
	EnvElements(glm::vec3 locomotivePosition);
	void setShader(const ShaderProgram& shader);
	void draw(glm::vec3 locomotivePosition);
};

