#include "EverGround.h"

void EverGround::update(){
	temperature = ofClamp(temperature + *sunniness, 5, 40);
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
	drawSun();
	backgroundTexture->draw();
}

void EverGround::drawSun(){
	ofSetCircleResolution(40);
	ofEnableAlphaBlending();
	ofSetColor(255, *sunniness * 35 + 220, 0);
	ofCircle(screenWidth/2, screenHeight - 800, *sunniness * 30 + 90);

	ofSetColor(255, *sunniness * 20 + 235, 0, *sunniness * 100);
	ofCircle(screenWidth/2, screenHeight - 800, *sunniness * 50 + 105);

	ofSetColor(255, *sunniness * 20 + 235, 0, *sunniness * 50);
	ofCircle(screenWidth/2, screenHeight - 800, *sunniness * 70 + 110);
	ofDisableAlphaBlending();
}

void EverGround::addFlowers(){
	if(health > 0.5 && numFlowers < 100 && ofRandomuf() < 0.01){
		flowers[numFlowers] = new EverFlower(ofPoint(ofRandom(900), 600 + ofRandom(200)));
		numFlowers++;

		//tree->adjustGrowthRate(-0.001);
	}
}

void EverGround::setControllerPointer(float* lWind, float* rWind, float* sun, float* shaky, int* plant){
	leftWind = lWind;
	rightWind = rWind;
	sunniness = sun;
	shakiness = shaky;
	plantType = plant;
}

void EverGround::setHealth(float health){
	this->health = health;
}

void EverGround::setTree(EverTree* tree){
	this->tree = tree;
}

EverGround::EverGround(int screenHeight, int screenWidth) {
	health = 1;
	numFlowers = 0;

	temperature = 20;

	float opacOffset = 0.1;

	numLayers = 2;
	deadLayer = new GrassTexture("environment/foreground/grass_0.png");
	deadLayer->setPosition(0,0);
	
	grassLayers[0] = new GrassTexture("environment/foreground/grass_0.5.png");
	grassLayers[0]->setPosition(0, screenHeight - grassLayers[0]->getHeight());

	grassLayers[1] = new GrassTexture("environment/foreground/grass_1.png");
	grassLayers[1]->setPosition(0, screenHeight - grassLayers[1]->getHeight());

	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	
	midgroundTexture = new SimpleTexture("environment/midground.png");
	backgroundTexture = new SimpleTexture("environment/background/mountains.png");
	skyTexture = new SimpleTexture("environment/background/sky.png");
	
	midgroundTexture->setPosition(0, screenHeight - midgroundTexture->getHeight());
	backgroundTexture->setPosition(0, screenHeight - backgroundTexture->getHeight());
	skyTexture->setPosition(0, 0);
	skyTexture->setSize(skyTexture->getWidth(), screenHeight);
}


EverGround::~EverGround(void)
{

}