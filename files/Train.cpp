#include "Train.h"
#include <iostream>

Train::Train()
{
	wagons.push_back(&w1);
	wagons.push_back(&w2);
}

Train::~Train()
{
	for (int i = wagons.size(); i > 1; --i)
		delete wagons.at(i);
	for (int i = 0; i < smoke.size(); ++i)
		delete smoke.at(i);
}

void Train::move(const glm::vec3& moveVector)
{
	float resistance = 0;
	if (moveVector.z != 0.0)
		resistance += deltaTime * (moveVector.z > 0 ? -1. : 1.) * 0.002;

	glm::vec3 sppedMove = moveVector * maxSpeed + glm::vec3{0, 0, resistance};
	if (std::abs(sppedMove.z) < 0.002)
		sppedMove = { 0,0,0 };
	locomotive.move(sppedMove);
	for (auto& w : wagons)
		w->move(sppedMove);
	calculateSmoke(locomotive.getPosition());
}

void Train::draw()
{
	locomotive.draw();
	for (auto w : wagons)
		w->draw();
	for (const auto& s : smoke)
		s->draw();
}

void Train::drawShadows()
{
	locomotive.setShader(Scene::getScene().simpleDepthShader);
	for (auto w : wagons)
		w->setShader(Scene::getScene().simpleDepthShader);
	locomotive.draw();
	for (auto w : wagons)
		w->draw();
	locomotive.setShader(Scene::getScene().shape_shader);
	for (auto w : wagons)
		w->setShader(Scene::getScene().shape_shader);
}

void Train::addWagon()
{
	try
	{
		if (wagons.size() <= max_wagons)
		{
			Wagon* w = new Wagon({ 0,1.02,3.2 * wagons.size()-0.2 +locomotive.getPosition().z });
			wagons.push_back(w);
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
}

void Train::deleteWagon()
{
	if (wagons.size() > min_wagons)
	{
		try
		{
			delete wagons.at(wagons.size() - 1);
			wagons.pop_back();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}
}

void Train::calculateSmoke(const glm::vec3& locPosition)
{
	int del = 0;
	static bool turn = 0;
	smokeTimeDiff -= deltaTime;

	if (smoke.size() < maxSmoke * 2 && smokeTimeDiff < 0)
	{
		auto offset = glm::vec3{ 0,0.6,-.4 };
		if (!turn)
			offset = glm::vec3{ 0,0.6,-1 };
		auto smk = new SmokeParticle(locPosition + offset, smokeLife);
		smoke.push_back(smk);
		turn = !turn;
		smokeTimeDiff = smokeLife / maxSmoke;
	}
	for (auto& s : smoke)
	{
		if (s->update(deltaTime))
		{
			delete s;
			++del;
		}
	}
	if (del > 0)
		smoke.erase(smoke.begin(), smoke.begin() + del);
}

void Train::update(float delta_time)
{
	deltaTime = delta_time;
}

void Train::setLightIntensity(float intensity)
{
	locomotive.set_light_intensity(intensity);
}

void Train::setLightColor(float r, float g, float b)
{
	locomotive.set_light_color(r, g, b);
}

glm::vec3 Train::getPosition()
{
	return locomotive.getPosition();
}
