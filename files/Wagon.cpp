#include "Wagon.h"

Wagon::Wagon(const glm::vec3& pos)
{
	wheelVector.push_back(&FrontWheels);
	wheelVector.push_back(&FrontWheels1);
	wheelVector.push_back(&BackWheels);
	wheelVector.push_back(&BackWheels1);
	WagonRoof.rotate({ 90,0,0 });
	this->Compartment.addElement(WagonRoof);
	this->Compartment.addElement(WagonBody);
	this->Compartment.addElement(WagonSuspension);
	this->Compartment.addElement(WagonConnection);
	move(pos);

}
void Wagon::draw()
{
	this->Compartment.draw();
	for (auto& w : wheelVector)
		w->draw();
}

void Wagon::setShader(const ShaderProgram& shader)
{
	this->Compartment.setShader(shader);
	for (auto& w : wheelVector)
		w->setShader(shader);
}

void Wagon::move(const glm::vec3& moveVector)
{
	float angle = moveVector.z * 360.0 / (2 * 3.1415 * 0.21);
	for (auto& w : wheelVector)
	{
		w->rotate({ angle,0,0 });
		w->move(moveVector);
	}
	Compartment.move(moveVector);
}