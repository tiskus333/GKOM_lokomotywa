#pragma once
#include "Composite.h"
#include "Cuboid.h"
class Cacti : public Composite
{
public:
	
	Cuboid cactiBase= Cuboid({ 0,0.6,0 }, { 0.2,1.2,0.2 }, glm::vec3(0.349, 0.467, 0.184));
	Cuboid cactiBranchLeft = Cuboid({ -0.3,0.7,0 }, { 0.4,0.2,0.2 }, glm::vec3(0.349, 0.467, 0.184));
	Cuboid cactiBranchRight = Cuboid({ 0.3,0.9,0 }, { 0.4,0.2,0.2 }, glm::vec3(0.349, 0.467, 0.184));
	Cuboid cactiStalkLeft = Cuboid({ -0.4,1,0 }, { 0.2,0.8,0.2 }, glm::vec3(0.349, 0.467, 0.184));
	Cuboid cactiStalkRight = Cuboid({ 0.4,1.1,0 }, { 0.2,0.4,0.2 }, glm::vec3(0.349, 0.467, 0.184));
	std::vector<Composite> cvec;
	
	

public:
	Cacti(const glm::vec3& position);

};

