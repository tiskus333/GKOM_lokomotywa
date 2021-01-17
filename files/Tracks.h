#pragma once
#include "Composite.h"
#include "Cuboid.h"
class Tracks
{
private:

	Cuboid leftTrackRail = Cuboid({ 0.45,0.05,0 }, { 0.1, 0.1, 1 },"metal0.png");
	Cuboid rightTrackRail = Cuboid({ -0.45,0.05,0 }, { 0.1, 0.1, 1 }, "metal0.png");
	Cuboid firstDiagonal = Cuboid({ 0,0.05,0.25 }, { 0.9, 0.09, 0.1 }, "wood.png");
	Cuboid secondDiagonal = Cuboid({ 0,0.05,-0.25 }, { 0.9, 0.09, 0.1 }, "wood.png");
	Composite track = Composite({ 0,0,0 });
	std::vector<Composite> comVec;
public:
	Tracks();
	void draw();
	void adjustPosition(const glm::vec3& train_pos);
};

