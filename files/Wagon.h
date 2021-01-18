#pragma once
#include "WagonWheels.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Composite.h"
class Wagon
{
	std::vector<WagonWheels*> wheelVector;
	WagonWheels FrontWheels = WagonWheels({ 0,-0.71,1.1 });
	WagonWheels FrontWheels1 = WagonWheels({ 0, -0.71, 0.65 });
	WagonWheels BackWheels = WagonWheels({ 0, -0.71, -0.65 });
	WagonWheels BackWheels1 = WagonWheels({ 0, -0.71, -1.1 });
	Cylinder WagonRoof = Cylinder({ 0,0.5,0 }, { 1,2.999,0.5 }, glm::vec3(0.874, 0.823, 0.862));
	Cuboid WagonBody = Cuboid({ 0,0,0 }, { 1,1,3 }, "wagon.png");
	Cuboid WagonSuspension = Cuboid({ 0,-0.6,0 }, { 0.75,0.2,2.8 }, glm::vec3(0.294, 0.294, 0.294));
	Cuboid WagonConnection = Cuboid({ 0,-0.6,-1.7 }, { 0.3,0.2,0.6 }, glm::vec3(0.294, 0.294, 0.294));
	Composite Compartment = Composite({ 0,0,0 });
public:
	Wagon(const glm::vec3& pos);
	void move(const glm::vec3& moveVector);
	void draw();
	void setShader(const ShaderProgram& shader);
	
};

