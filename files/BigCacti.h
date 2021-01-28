#pragma once
#include "Cacti.h"
class BigCacti : public Composite
{
public:

	Cuboid cactiBase = Cuboid({ 0,1.8,0 }, { 0.2,3.6,0.2 }, glm::vec3(0.349, 0.367, 0.184));
	Cuboid cactiBranchLeft = Cuboid({ -0.4,1.8,0 }, { 0.7,0.2 ,0.2 }, glm::vec3(0.349, 0.367, 0.184));
	Cuboid cactiBranchRight = Cuboid({ 0.4,2.7 ,0 }, { 0.7,0.2 ,0.2 }, glm::vec3(0.349, 0.367, 0.184));
	Cuboid cactiStalkLeft = Cuboid({ -0.65,3,0 }, { 0.2,2.4,0.2 }, glm::vec3(0.349, 0.367, 0.184));
	Cuboid cactiStalkRight = Cuboid({ 0.65,3.3,0 }, { 0.2,1.2,0.2 }, glm::vec3(0.349, 0.367, 0.184));
	std::vector<Composite> cvec;



public:
	BigCacti(const glm::vec3& position);

};

