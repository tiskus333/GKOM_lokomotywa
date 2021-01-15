#pragma once
#include "Composite.h"
#include "Cuboid.h"
class Tracks
{
private:

	Cuboid leftTrackRail = Cuboid({ 0.45,0.05,0 }, { 0.1, 0.1, 1 }, glm::vec3(1, 0, 1));
	Cuboid rightTrackRail = Cuboid({ -0.45,0.05,0 }, { 0.1, 0.1, 1 }, glm::vec3(1, 0, 1));
	Cuboid firstDiagonal = Cuboid({ 0,0.05,0.25 }, { 0.9, 0.09, 0.1 }, glm::vec3(1, 4, 1));
	Cuboid secondDiagonal = Cuboid({ 0,0.05,-0.25 }, { 0.9, 0.09, 0.1 }, glm::vec3(1, 4, 1));
	Composite track = Composite({ 0,0,0 });
	std::vector<Composite> comVec;
public:
	Tracks();
	void draw();
};

