#include "EnvElements.h"
EnvElements::EnvElements(glm::vec3 locomotivePosition) {
	

	for (int i = 0; i < 80; i++)
	{
		auto a = rand() % 15 + 5;
		auto b = rand() % 90 ;
		b -= 45;
		auto c = rand() % 90;
		cacti.setPosition({ a,0 , locomotivePosition.z - b });
		cacti.rotate({ 0,c,0 });
		cvec.emplace_back(cacti);

		auto a1 = (rand() % 15 + 5) * -1;
		auto b1 = rand() % 90 ;
		b1 -= 45;
		auto c1 = rand() % 90;
		cacti.rotate({ 0,c1,0 });
		cacti.setPosition({ a1,0 ,locomotivePosition.z - b1 });
		cvec.emplace_back(cacti);
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
			auto a = rand() % 15 + 5;
			auto b = rand() % 15 + 30;

			auto c = rand() % 90;
			cacti.setPosition({ a,0 , locomotivePosition.z - b });
			cacti.rotate({ 0,c,0 });
			cvec.emplace_back(cacti);

			auto a1 = (rand() % 15 + 5) * -1;
			auto b1 = rand() % 15 + 30;
			auto c1 = rand() % 90;
			cacti.rotate({ 0,c1,0 });
			cacti.setPosition({ a1,0 ,locomotivePosition.z - b1 });
			cvec.emplace_back(cacti);
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
			auto a = rand() % 15 + 5;
			auto b = rand() % 15 + 30;

			auto c = rand() % 90;
			cacti.setPosition({ a,0 , locomotivePosition.z + b });
			cacti.rotate({ 0,c,0 });
			cvec.emplace(cvec.begin(),cacti);

			auto a1 = (rand() % 15 + 5) * -1;
			auto b1 = rand() % 15 + 30;
			auto c1 = rand() % 90;
			cacti.rotate({ 0,c1,0 });
			cacti.setPosition({ a1,0 ,locomotivePosition.z + b1 });
			cvec.emplace(cvec.begin(), cacti);
		}

		LastLocomotivePosition = locomotivePosition;
		for (auto& w : cvec) {
			w.draw();
		}
	}

}