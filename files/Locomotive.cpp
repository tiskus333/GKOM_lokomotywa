#include "Locomotive.h"
#include <iostream>

Locomotive::Locomotive(const glm::vec3& pos)
{
	wheelVector.push_back(&FrontWheels2);
	wheelVector.push_back(&FrontWheels1);
	wheelVector.push_back(&BackWheels2);
	wheelVector.push_back(&BackWheels1);
	DriverBoothRoof.rotate({ 90,0,0 });
	LocomotiveHullRoof.rotate({ 90,0,0 });
	LocomotiveHeadlight.rotate({ 90,0,0 });

	Loc.addElement(DriverBoothBody);
	Loc.addElement(DriverBoothRoof);
	Loc.addElement(LocomotiveHull);
	Loc.addElement(LocomotiveHullRoof);
	Loc.addElement(Chimney1);
	Loc.addElement(ChimneyTop1);
	Loc.addElement(Chimney2);
	Loc.addElement(ChimneyTop2);
	Loc.addElement(LocomotiveSuspension);
	Loc.addElement(LocomotiveHeadlight);
		
	FrontWheels1.addElement(BailRight);
	FrontWheels1.addElement(BailLeft);

	move(pos);
}

void Locomotive::draw()
{
	static bool light_set = false;
	Loc.draw();

	for (auto w : wheelVector)
		w->draw();
		if (!light_set)
	{
		light_set = true;
		Scene::getScene().light_directions[LocomotiveHeadlight.number_of_light_] = glm::vec3(0.0, 0.0, 0.002);
	}
}

void Locomotive::setShader(const ShaderProgram& shader)
{

	Loc.setShader(shader);

	for (auto w : wheelVector)
		w->setShader(shader);
	Loc.getElement(9)->setShader(Scene::getScene().light_shader);
}

void Locomotive::set_light_intensity(float intensity) {

	Loc.getElement(9)->setColor( intensity, intensity, intensity );
}
void Locomotive::set_light_color(float r, float g, float b) {

	Loc.getElement(9)->setColor(r, g, b);
}

void Locomotive::move(const glm::vec3& moveVector)
{
	float angle = moveVector.z * 360.0 / (2 * 3.1415 * 0.21);
	for (auto w : wheelVector)
	{
		w->rotate({ angle,0,0 });
		w->move(moveVector);
		
	}

	BailRight.rotate({ -angle,0,0 }, { 0.51,0.13,-0.05 });
	BailLeft.rotate({ -angle,0,0 }, { -0.51,0.13,-0.05 });
	
	Loc.move(moveVector);
}
glm::vec3 Locomotive::getPosition()
{
	return Loc.position_;
}