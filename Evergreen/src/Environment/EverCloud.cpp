#include "EverCloud.h"


EverCloud::EverCloud(void)
{
	cloud = new EverTexture("environment/background/clouds/cloud_01.png");
	speed = 0.1;
	posx = ofRandomuf() * 1280;
	posy = ofRandomuf() * 1600 - 300;

	sizePercent = ofRandom(1.0, 5.0);
	width = cloud->getWidth() * sizePercent;
	height = cloud->getHeight() * sizePercent;
}

void EverCloud::update(){
	if(posx < -width) posx = 1280;
	if(posx > 1280) posx = -width;

	posx += speed;
}

void EverCloud::draw() {
	cloud->draw(posx, posy, width, height);
}

void EverCloud::setOpacity(float alpha){
	cloud->setOpacity(alpha);
}


EverCloud::~EverCloud(void)
{
}
