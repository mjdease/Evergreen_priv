#include "EverCloud.h"


EverCloud::EverCloud(void)
{
	cloud = new EverTexture("environment/background/clouds/cloud_01.png");
	speed = 0.1;
	posx = ofRandomuf() * 1280;
	posy = ofRandomuf() * 1600 - 300;
}

void EverCloud::draw() {
	posx += speed;
	if(posx < 0) posx = 1280;
	cloud->draw(posx, posy);
}


EverCloud::~EverCloud(void)
{
}
