#include "EnvElements.h"
EnvElements::EnvElements(glm::vec3 locomotivePosition) {
	

	for (int i = 0; i < 80; i++)
	{
		auto x = rand() % 15 + 5;
		auto z = rand() % 90;
		z -= 45;
		auto angle = rand() % 90;
		if (angle < 70) {


			cacti.setPosition({ x,0 , locomotivePosition.z - z });
			cacti.rotate({ 0,angle,0 });
			cvec.emplace_back(cacti);
		}
		else {
			bigCacti.setPosition({ x,0 , locomotivePosition.z - z });
			bigCacti.rotate({ 0,angle,0 });
			cvec.emplace_back(bigCacti);
		}
		auto x1 = (rand() % 15 + 5) * -1;
		auto z1 = rand() % 90;
		z1 -= 45;
		auto angle1 = rand() % 90;
		if (angle1 < 70) {


			cacti.setPosition({ x1,0 , locomotivePosition.z - z1 });
			cacti.rotate({ 0,angle1,0 });
			cvec.emplace_back(cacti);
		}
		else {
			bigCacti.setPosition({ x1,0 , locomotivePosition.z - z1 });
			bigCacti.rotate({ 0,angle1,0 });
			cvec.emplace_back(bigCacti);
		}
	}

}
void EnvElements::setShader(const ShaderProgram& shader) {
	for (auto& w : cvec) {
		w.setShader(shader);
	}
}
void EnvElements::draw(glm::vec3 locomotivePosition) {


	
	if (abs(locomotivePosition.z - LastLocomotivePosition.z) < 15 ) {
		for (auto& w : cvec) {
			w.draw();
		}
	}
	else  if (locomotivePosition.z - LastLocomotivePosition.z < 15)
	{
		cvec.erase(cvec.begin(), cvec.begin() + 24);
		for (int i = 0; i < 12; i++)
		{
			auto x = rand() % 15 + 5;
			auto z = rand() % 15 + 30;

			auto angle = rand() % 90; 
			if (angle < 70) {


				cacti.setPosition({ x,0 , locomotivePosition.z - z });
				cacti.rotate({ 0,angle,0 });
				cvec.emplace_back(cacti);
			}
			else {
				bigCacti.setPosition({ x,0 , locomotivePosition.z - z });
				bigCacti.rotate({ 0,angle,0 });
				cvec.emplace_back(bigCacti);
			}

			auto x1 = (rand() % 15 + 5) * -1;
			auto z1 = rand() % 15 + 30;
			auto angle1 = rand() % 90;
			if (angle1 < 70) {


				cacti.setPosition({ x1,0 , locomotivePosition.z - z1 });
				cacti.rotate({ 0,angle1,0 });
				cvec.emplace_back(cacti);
			}
			else {
				bigCacti.setPosition({ x1,0 , locomotivePosition.z - z1 });
				bigCacti.rotate({ 0,angle1,0 });
				cvec.emplace_back(bigCacti);
			}
		}
		
		LastLocomotivePosition = locomotivePosition;
		for (auto& w : cvec) {
			w.draw();
		}
	}
	else {
		cvec.erase(cvec.end()- 24, cvec.end());
		for (int i = 0; i < 12; i++)
		{
			auto x = rand() % 15 + 5;
			auto z = rand() % 15 + 30;

			auto angle = rand() % 90;
			if (angle < 70)
			{
				cacti.setPosition({ x,0 , locomotivePosition.z + z });
				cacti.rotate({ 0,angle,0 });
				cvec.emplace(cvec.begin(), cacti);
			}
			else
			{
				bigCacti.setPosition({ x,0 , locomotivePosition.z + z });
				bigCacti.rotate({ 0,angle,0 });
				cvec.emplace(cvec.begin(), bigCacti);
			}
			auto x1 = (rand() % 15 + 5) * -1;
			auto z1 = rand() % 15 + 30;
			auto angle1 = rand() % 90;
			if (angle1 < 70)
			{
				cacti.rotate({ 0,angle1,0 });
				cacti.setPosition({ x1,0 ,locomotivePosition.z + z1 });
				cvec.emplace(cvec.begin(), cacti);
			}
			else 
			{
				bigCacti.rotate({ 0,angle1,0 });
				bigCacti.setPosition({ x1,0 ,locomotivePosition.z + z1 });
				cvec.emplace(cvec.begin(), bigCacti);
			}
			
		}

		LastLocomotivePosition = locomotivePosition;
		for (auto& w : cvec) {
			w.draw();
		}
	}

}