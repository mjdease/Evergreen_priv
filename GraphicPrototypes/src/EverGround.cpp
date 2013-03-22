#include "EverGround.h"

EverGround::EverGround(void)
{
	numLayers = 2;

	grassLayers[0] = new GrassTexture("grassTexture.png");
}

void EverGround::draw(){
	for(int i=0; i<numLayers; i++){
		grassLayers[i]->setOpacity(123);
		grassLayers[i]->setPosition(0, ofGetHeight() - grassLayers[i]->getHeight());
		grassLayers[i]->draw(0);
	}
}

EverGround::~EverGround(void)
{
}
