#include "WagonWheels.h"

WagonWheels::WagonWheels(const glm::vec3& position) : Composite(position)
{
	CompartmentWheel1.rotate({ 0,0,90 });
	CompartmentWheel2.rotate({ 0,0,90 });
	this->addElement(CompartmentWheel1);
	this->addElement(CompartmentWheel2);
	this->addElement(Bar);
}

