#include "EnvElements.h"
EnvElements::EnvElements(glm::vec3 locomotivePosition) {
	Composite* baseCacti;
	for (int i = chunk_count; i >= -chunk_count; --i)
	{
		for (int c = 0; c < cacti_per_chunk; ++c)
		{
			auto side = rand() % 2 ? -1 : 1;
			auto x = rand() % cacti_spread + 5;
			auto z = chunk_size * i + rand() % chunk_size;
			auto angle = rand() % 90;
			if (angle < 70) 
				baseCacti = &cacti;
			else 
				baseCacti = &bigCacti;
			baseCacti->setPosition({ x*side,0 , z });
			baseCacti->rotate({ 0,angle,0 });
			cvec.push_back(*baseCacti);
		}
	}

}
void EnvElements::setShader(const ShaderProgram& shader) {
	for (auto& w : cvec) {
		w.setShader(shader);
	}
}

void EnvElements::adjustPosition(const glm::vec3& locomotivePosition) {
	float displacement = LastLocomotivePosition.z - locomotivePosition.z;
	int direction = displacement > 0 ? -1 : 1;
	Composite* baseCacti;

	if (std::abs(displacement) >= chunk_size)
	{
		if (direction < 0)
			cvec.erase(cvec.begin(), cvec.begin() + cacti_per_chunk);
		else
			cvec.erase(cvec.end()-cacti_per_chunk, cvec.end());
		for (int c = 0; c < cacti_per_chunk; ++c)
		{
			auto side = rand() % 2 ? -1 : 1;
			auto x = rand() % cacti_spread + 5;
			auto z = (int)std::floor(locomotivePosition.z) + direction*chunk_size * (chunk_count)  + rand() % chunk_size;
			auto angle = rand() % 90;
			if (angle < 70)
				baseCacti = &cacti;
			else
				baseCacti = &bigCacti;
			baseCacti->setPosition({ x * side,0 , z });
			baseCacti->rotate({ 0,angle,0 });
			if (direction < 0)
				cvec.push_back(*baseCacti);
			else
				cvec.insert(cvec.begin(), *baseCacti );
		}
		LastLocomotivePosition = locomotivePosition;
	}
}

void EnvElements::draw() {
	for (auto& w : cvec) 
		w.draw();
}