#pragma once
#include "Composite.h"
#include "WagonWheels.h"
#include "Cylinder.h"
#include "Cuboid.h"
class Locomotive 
{
	std::vector<WagonWheels*> wheelVector;
	Cylinder DriverBoothRoof = Cylinder({ 0,0.5,0.85 }, { 1,0.799,0.5 }, glm::vec3(0.874, 0.823, 0.862));
	Cuboid DriverBoothBody = Cuboid({ 0,0,0.85 }, { 1,1,0.8 }, "kabina.png");
	Cylinder LocomotiveHullRoof = Cylinder({ 0,-0.1,-0.35 }, { 1,1.799, 0.4 }, glm::vec3(0.819, 0.455, 0.314));
	Cuboid LocomotiveHull = Cuboid({ 0,-0.3,-0.35 }, { 1,0.4,1.8 }, glm::vec3(0.819, 0.455, 0.314));
	Cuboid Chimney1 = Cuboid({ 0,0.2,-0.4 }, { 0.2,0.6,0.2 }, glm::vec3(0.294, 0.294, 0.294));
	Cuboid ChimneyTop1 = Cuboid({ 0,0.5,-0.4 }, { 0.3,0.1,0.3 }, glm::vec3(0.294, 0.294, 0.294));
	Cuboid Chimney2 = Cuboid({ 0,0.2,-1.0 }, { 0.2,0.6,0.2 }, glm::vec3(0.294, 0.294, 0.294));
	Cuboid ChimneyTop2 = Cuboid({ 0,0.5,-1.0 }, { 0.3,0.1,0.3 }, glm::vec3(0.294, 0.294, 0.294));
	WagonWheels FrontWheels1 = WagonWheels({ 0,-0.71,1.0 });
	WagonWheels FrontWheels2 = WagonWheels({ 0, -0.71, 0.55 });
	WagonWheels BackWheels1 = WagonWheels({ 0, -0.71, -0.55 });
	WagonWheels BackWheels2 = WagonWheels({ 0, -0.71, -1.0 });
	Cuboid LocomotiveSuspension = Cuboid({ 0,-0.6,0 }, { 0.75,0.2,2.4 }, glm::vec3(0.294, 0.294, 0.294));
	Cylinder LocomotiveHeadlight = Cylinder({ 0,-0.2,-1.3 }, { 0.3,0.1,0.3 }, glm::vec3(1, 1, 1), true);
	Cuboid BailRight = Cuboid({ 0.51,0.13,- 1.05 }, { 0.02,0.07,2.05 }, glm::vec3(0.294, 0.294, 0.294));
	Cuboid BailLeft = Cuboid({ -0.51,0.13,- 1.05 }, { 0.02,0.07,2.05 }, glm::vec3(0.294, 0.294, 0.294));
	
	Composite Loc = Composite({ 0,0,0 });
public:
	Locomotive(const glm::vec3& pos);
	void move(const glm::vec3& moveVector);
	glm::vec3 getPosition();
	void draw();
	void setShader(const ShaderProgram& shader);
	void set_light_intensity(float intensity);
	void set_light_color(float r, float g, float b);
};

