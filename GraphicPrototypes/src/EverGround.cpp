#include "EverGround.h"

EverGround::EverGround(void) {
	float opacOffset = 0.1;
	numLayers = 2;
	deadLayer = new GrassTexture("grass_0.png");
	deadLayer->setPosition(0,0);
	
	grassLayers[0] = new GrassTexture("environment/foreground/grass_0.5.png");
	grassLayers[1] = new GrassTexture("environment/foreground/grass_1.png");
}

void EverGround::draw(){
	deadLayer->draw(0);

	for(int i=0; i<numLayers; i++) {
		grassLayers[i]->draw(0);
		grassLayers[i]->setPosition(0, ofGetHeight() - grassLayers[i]->getHeight());
	}
	
	if(health > 0.1) 
		grassLayers[0]->setOpacity(255*health);
	if(health > 0.7) 
		grassLayers[1]->setOpacity(255*health);
}

EverGround::~EverGround(void)
{

}