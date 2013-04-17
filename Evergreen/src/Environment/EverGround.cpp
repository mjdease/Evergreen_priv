#include "EverGround.h"

EverGround::EverGround(int screenHeight) {
	health = 1;
	numFlowers = 0;

	float opacOffset = 0.1;

	numLayers = 2;
	deadLayer = new GrassTexture("environment/foreground/grass_0.png");
	deadLayer->setPosition(0,0);
	
	grassLayers[0] = new GrassTexture("environment/foreground/grass_0.5.png");
	grassLayers[0]->setPosition(0, screenHeight - grassLayers[0]->getHeight());

	grassLayers[1] = new GrassTexture("environment/foreground/grass_1.png");
	grassLayers[1]->setPosition(0, screenHeight - grassLayers[1]->getHeight());

	this->screenHeight = screenHeight;
	
	midgroundTexture = new SimpleTexture("environment/midground.png");
	backgroundTexture = new SimpleTexture("environment/background/mountains.png");
	skyTexture = new SimpleTexture("environment/background/sky.png");
	
	midgroundTexture->setPosition(0, screenHeight - midgroundTexture->getHeight());
	backgroundTexture->setPosition(0, screenHeight - backgroundTexture->getHeight());
	skyTexture->setPosition(0, 0);
	skyTexture->setSize(skyTexture->getWidth(), screenHeight);
}

void EverGround::draw(){
	//deadLayer->draw(0);
	//displayManager->addtoLayer(deadLayer, 0);

	if(health < 0.5){
		grassLayers[1]->setOpacity(0);
		grassLayers[0]->setOpacity(health/0.5 * 255);
	}
	else{
		grassLayers[0]->setOpacity(255);
		grassLayers[1]->setOpacity((health-0.5)/0.5 * 255);
	}

	for(int i=0; i<numLayers; i++) {
		//displayManager->addtoLayer(grassLayers[i], 0);
		grassLayers[i]->draw(0);
	}

	addFlowers();
	for(int i=0; i<numFlowers; i++){
		//flowers[i]->draw(0);
		//displayManager->addtoLayer(flowers[i], 0);
	}
}

void EverGround::drawMidground(){
	midgroundTexture->draw();
}

void EverGround::drawBackground(){
	skyTexture->draw();
	backgroundTexture->draw();
}

void EverGround::addFlowers(){
	if(health > 0.5 && numFlowers < 100 && ofRandomuf() < 0.01){
		flowers[numFlowers] = new EverFlower(ofPoint(ofRandom(900), 600 + ofRandom(200)));
		numFlowers++;

		//tree->adjustGrowthRate(-0.001);
	}
}

void EverGround::setHealth(float health){
	this->health = health;
}

void EverGround::setTree(EverTree* tree){
	this->tree = tree;
}

EverGround::~EverGround(void)
{

}