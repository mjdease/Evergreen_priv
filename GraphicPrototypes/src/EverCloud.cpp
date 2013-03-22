#include "EverCloud.h"


EverCloud::EverCloud(void)
{
	cloud = new EverTexture("environment/background/clouds/cloud_01.png");
	spd = 3;
	posx = 1280;
	posy = 10;
}

void EverCloud::draw() {

	posx -= spd;
	cloud->draw(posx, posy);

}


EverCloud::~EverCloud(void)
{
}
