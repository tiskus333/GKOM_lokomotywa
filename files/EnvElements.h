#pragma once
#include "Cacti.h"
#include "BigCacti.h"
class EnvElements
{
private:
	std::vector<Composite> cvec;
	glm::vec3 LastLocomotivePosition;
	Cacti cacti = Cacti({ 0,0,0 });
	BigCacti bigCacti = BigCacti({ 0,0,0 });
	int cacti_per_chunk = 20;
	int cacti_spread = 20;
	int chunk_size = 20;
	int chunk_count = 5;

public:
	EnvElements(glm::vec3 locomotivePosition);
	void setShader(const ShaderProgram& shader);
	void draw();
	void adjustPosition(const glm::vec3& locomotivePosition);
};

