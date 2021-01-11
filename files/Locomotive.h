#pragma once
#include "Composite.h"
#include "WagonWheels.h"
#include "Cylinder.h"
#include "Cuboid.h"
class Locomotive 
{
	std::vector<WagonWheels*> wheelVector;
	Cylinder DriverBoothRoof = Cylinder({ 0,0.5,0.85 }, { 1,0.7999,0.5 }, glm::vec3(0, 0, 1));
	Cuboid DriverBoothBody = Cuboid({ 0,0,0.85 }, { 1,1,0.8 }, glm::vec3(1, 0.5, 1));
	Cylinder LocomotiveHullRoof = Cylinder({ 0,-0.1,-0.35 }, { 1,1.799, 0.4 }, glm::vec3(0, 0, 1));
	Cuboid LocomotiveHull = Cuboid({ 0,-0.3,-0.35 }, { 1,0.4,1.8 }, glm::vec3(1, 0.5, 1));
	Cuboid Chimney = Cuboid({ 0,0.2,-0.4 }, { 0.2,0.6,0.2 }, glm::vec3(0, 0, 0));
	Cuboid ChimneyTop = Cuboid({ 0,0.5,-0.4 }, { 0.3,0.1,0.3 }, glm::vec3(0, 0, 0));
	Cuboid Chimney1 = Cuboid({ 0,0.2,-1.0 }, { 0.2,0.6,0.2 }, glm::vec3(0, 0, 0));
	Cuboid ChimneyTop1 = Cuboid({ 0,0.5,-1.0 }, { 0.3,0.1,0.3 }, glm::vec3(0, 0, 0));
	WagonWheels FrontWheels = WagonWheels({ 0,-0.71,1.0 });
	WagonWheels FrontWheels1 = WagonWheels({ 0, -0.71, 0.55 });
	WagonWheels BackWheels = WagonWheels({ 0, -0.71, -0.55 });
	WagonWheels BackWheels1 = WagonWheels({ 0, -0.71, -1.0 });
	Cuboid LocomotiveSuspension = Cuboid({ 0,-0.6,0 }, { 0.75,0.2,2.4 }, glm::vec3(0, 2, 1));
	Cylinder LocomotiveHeadlight = Cylinder({ 0,-0.2,-1.3 }, { 0.3,0.1,0.3 }, glm::vec3( 10,10,1 ), true);
	Cuboid Bail = Cuboid({0.51,-0.58,-0.0}, {0.02,0.07,2.1}, glm::vec3(1,1,1));
	Cuboid Bail1 = Cuboid({ -0.51,-0.58,-0.0 }, { 0.02,0.07,2.1 }, glm::vec3(1, 1, 1));
	Cuboid Bail3 = Cuboid({ 0.51,-0.58+0.71,-0.0-1 }, { 0.02,0.07,2.1 }, glm::vec3(1, 1, 1));
	Composite Loc = Composite({ 0,0,0 });
public:
	Locomotive();
	void move(glm::vec3);
	void draw();
};

