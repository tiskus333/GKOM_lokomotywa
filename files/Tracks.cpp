#include "Tracks.h"
Tracks::Tracks() {
	track.addElement(leftTrackRail);
	track.addElement(rightTrackRail);
	track.addElement(firstDiagonal);
	track.addElement(secondDiagonal);

	for (int i = -100; i < 101; i++)
	{
		track.setPosition({ 0,0,i });
		comVec.push_back(track);
	}
}
void Tracks::draw() {
	
	for (auto& i : comVec)
	{
		i.draw();
	}

}
void Tracks::adjustPosition(const glm::vec3& train_pos)
{
	for (auto i = 0; i < comVec.size(); ++i)
	{
		comVec[i].setPosition({ 0,0,std::floor(train_pos.z) + i - 101 });
	}
}