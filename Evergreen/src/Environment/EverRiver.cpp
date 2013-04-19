#include "EverRiver.h"

EverRiver::EverRiver(float x, float y, float* water)
{
	riverSound = new Audio("audio/RiverInOut.mp3");
	riverSound->start();

	this->x = x;
	this->y = y;

	loadImages();
	waterLevel = water;
	frameNum = 1;
	frameDir = 1;
	drawnFg = fgRiver1;
}

void EverRiver::update(){
	riverSound->setVol(*waterLevel / 100);

	if(*waterLevel < 25)
		drawnFg = fgRiver1;
	else if(*waterLevel < 50)
		drawnFg = fgRiver2;
	else if(*waterLevel < 75)
		drawnFg = fgRiver3;
	else
		drawnFg = fgRiver4;

	if(ofGetFrameNum()%30 == 0){
		if(frameNum == 0 || frameNum == 3){
			frameDir *= -1;
		}
		frameNum += frameDir;
	}
}

void EverRiver::drawForeground() {
		drawnFg[int(frameNum)]->draw(x,y);
}

void EverRiver::drawMidground() {
	if(*waterLevel < 25)
		mgRiver[0]->draw(x, y);
	else if(*waterLevel < 50)
		mgRiver[1]->draw(x, y);
	else if(*waterLevel < 75)
		mgRiver[2]->draw(x, y);
	else
		mgRiver[3]->draw(x, y);
}

void EverRiver::loadImages(){

	fgRiver1[0] = new EverTexture();
	fgRiver1[1] = new EverTexture();
	fgRiver1[2] = new EverTexture();
	fgRiver1[3] = new EverTexture();
	
	fgRiver1[0]->loadTexture("environment/river/river_fg_00a.png");
	fgRiver1[1]->loadTexture("environment/river/river_fg_00b.png");
	fgRiver1[2]->loadTexture("environment/river/river_fg_00c.png");
	fgRiver1[3]->loadTexture("environment/river/river_fg_00c.png");
	
	fgRiver2[0] = new EverTexture();
	fgRiver2[1] = new EverTexture();
	fgRiver2[2] = new EverTexture();
	fgRiver2[3] = new EverTexture();
	
	fgRiver2[0]->loadTexture("environment/river/river_fg_01a.png");
	fgRiver2[1]->loadTexture("environment/river/river_fg_01b.png");
	fgRiver2[2]->loadTexture("environment/river/river_fg_01c.png");
	fgRiver2[3]->loadTexture("environment/river/river_fg_01c.png");
	
	fgRiver3[0] = new EverTexture();
	fgRiver3[1] = new EverTexture();
	fgRiver3[2] = new EverTexture();
	fgRiver3[3] = new EverTexture();
	
	fgRiver3[0]->loadTexture("environment/river/river_fg_02a.png");
	fgRiver3[1]->loadTexture("environment/river/river_fg_02b.png");
	fgRiver3[2]->loadTexture("environment/river/river_fg_02c.png");
	fgRiver3[3]->loadTexture("environment/river/river_fg_02c.png");
	
	fgRiver4[0] = new EverTexture();
	fgRiver4[1] = new EverTexture();
	fgRiver4[2] = new EverTexture();
	fgRiver4[3] = new EverTexture();
	
	fgRiver4[0]->loadTexture("environment/river/river_fg_03a.png");
	fgRiver4[1]->loadTexture("environment/river/river_fg_03b.png");
	fgRiver4[2]->loadTexture("environment/river/river_fg_03c.png");
	fgRiver4[3]->loadTexture("environment/river/river_fg_03c.png");
	
	mgRiver[0] = new EverTexture();
	mgRiver[1] = new EverTexture();
	mgRiver[2] = new EverTexture();
	mgRiver[3] = new EverTexture();
	
	mgRiver[0]->loadTexture("environment/river/river_mg_00a.png");
	mgRiver[1]->loadTexture("environment/river/river_mg_01a.png");
	mgRiver[2]->loadTexture("environment/river/river_mg_02a.png");
	mgRiver[3]->loadTexture("environment/river/river_mg_03a.png");
}

EverRiver::~EverRiver(void)
{
}