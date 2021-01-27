#include "BigCacti.h"
BigCacti::BigCacti(const glm::vec3& position) :Composite(position) {
	this->addElement(cactiBase);
	this->addElement(cactiBranchRight);
	this->addElement(cactiBranchLeft);
	this->addElement(cactiStalkLeft);
	this->addElement(cactiStalkRight);
}