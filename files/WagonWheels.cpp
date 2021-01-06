#include "WagonWheels.h"

WagonWheels::WagonWheels() : Composite({ 0,0,0 })
{
	

	this->addElement(CompartmentWheel1);
	this->addElement(CompartmentWheel2);
	this->addElement(Bar);
	this->position_ = position_;
}

