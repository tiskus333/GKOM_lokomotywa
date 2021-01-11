#include "Locomotive.h"

Locomotive::Locomotive()
{
	wheelVector.push_back(&FrontWheels);
	wheelVector.push_back(&FrontWheels1);
	wheelVector.push_back(&BackWheels);
	wheelVector.push_back(&BackWheels1);
	DriverBoothRoof.rotate({ 90,0,0 });
	LocomotiveHullRoof.rotate({ 90,0,0 });
	LocomotiveHeadlight.rotate({ 90,0,0 });

	Loc.addElement(DriverBoothBody);
	Loc.addElement(DriverBoothRoof);
	Loc.addElement(LocomotiveHull);
	Loc.addElement(LocomotiveHullRoof);
	Loc.addElement(Chimney);
	Loc.addElement(ChimneyTop);
	Loc.addElement(Chimney1);
	Loc.addElement(ChimneyTop1);
	Loc.addElement(LocomotiveSuspension);
	Loc.addElement(LocomotiveHeadlight);
	//Loc.addElement(Bail);
	//Loc.addElement(Bail1);
	FrontWheels.addElement(Bail3);
}

void Locomotive::draw()
{
	Loc.draw();
	Bail.draw();
	Bail1.draw();
	//Bail3.draw();
	for (auto w : wheelVector)
		w->draw();
}

void Locomotive::move(const glm::vec3 moveVector)
{
	float angle = moveVector.z * 360.0 / (2 * 3.1415 * 0.21);
	for (auto w : wheelVector)
	{
		//w->rotate({ angle,0,0 });
		w->move(moveVector);
		
	}
	Bail3.rotate({ -angle,0,0 });
	Bail3.draw();
	Loc.move(moveVector);
}