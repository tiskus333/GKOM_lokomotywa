#include "Wagon.h"

Wagon::Wagon()
{
	/*wheelVector.push_back(FrontWheels);
	wheelVector.push_back(FrontWheels1);
	wheelVector.push_back(BackWheels);
	wheelVector.push_back(BackWheels1);*/
	WagonRoof.rotate({ 90,0,0 });
	this->Compartment.addElement(WagonRoof);
	this->Compartment.addElement(WagonBody);
	this->Compartment.addElement(WagonSuspension);

}
void Wagon::draw()
{
	this->Compartment.draw();
	this->BackWheels.draw();
	this->BackWheels1.draw();
	this->FrontWheels.draw();
	this->FrontWheels1.draw();
	/*for (auto& w:wheelVector)
	{
		w.draw();
	}*/
}

void Wagon::move(const glm::vec3 moveVector)
{

	float angle = moveVector.z * 360.0 / (2 * 3.1415 * 0.21);
	BackWheels.rotate({ angle,0,0 });
	BackWheels1.rotate({ angle,0,0 });
	FrontWheels.rotate({ angle,0,0 });
	FrontWheels1.rotate({ angle,0,0 });
	Compartment.move(moveVector);
	BackWheels.move(moveVector);
	BackWheels1.move(moveVector);
	FrontWheels.move(moveVector);
	FrontWheels1.move(moveVector);
}