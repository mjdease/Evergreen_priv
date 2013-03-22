#include "EverCloud.h"


EverCloud::EverCloud(void)
{
	cloud = new EverTexture("environment/background/clouds/cloud_01.png");
	spd = 0.1;
	posx = ofRandomuf() * 1280;
	posy = 300 - ofRandomuf() * 2700;
}

void EverCloud::draw(float offset) {

	posx -= spd;
	if(posx < 0) posx = 1280;
	cloud->draw(posx, posy+offset);

}


EverCloud::~EverCloud(void)
{
}
