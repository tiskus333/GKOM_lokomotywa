#pragma once
#include "Locomotive.h"
#include "Wagon.h"
#include "Tracks.h"
#include "SmokeParticle.h"
class Train
{
	std::vector<Wagon*> wagons;
	int max_wagons = 10;
	int min_wagons = 2;

	std::vector<SmokeParticle*> smoke;
	float smokeLife = 2;
	float smokeTimeDiff = smokeLife / maxSmoke;

	float deltaTime;
	float maxSpeed = 0.7f;

	Locomotive locomotive = Locomotive({ 0,1.02,0 });
	Wagon w1 = Wagon({ 0,1.02,3 });
	Wagon w2 = Wagon({ 0,1.02,6.2 });
public:
	int maxSmoke = 5;
	Train();
	~Train();
	void move(const glm::vec3& moveVector);
	void draw();
	void drawShadows();
	void addWagon();
	void deleteWagon();
	void calculateSmoke(const glm::vec3& locPosition);
	void update(float delta_time);
	void setLightIntensity(float intensity);
	void setLightColor(float r, float g, float b);
	glm::vec3 getPosition();

};

