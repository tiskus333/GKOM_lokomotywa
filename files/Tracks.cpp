#include "Tracks.h"
Tracks::Tracks() {
	track.addElement(leftTrackRail);
	track.addElement(rightTrackRail);
	track.addElement(firstDiagonal);
	track.addElement(secondDiagonal);

	for (int i = -100; i < 100; i++)
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