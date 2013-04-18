#include "EverGround.h"

#define cloudNum 30
#define flowerNum 50
#define thornNum 20

EverGround::EverGround(int screenHeight, int screenWidth, bool* paused) {
	this->paused = paused;
	grassHealth = 0;
	numFlowers = numThorns = 0;

	temperature = 20;
	wind = 10;
	cloudLevel = 0; 
	rainAmount = 0;
	waterLevel = 1.0f;
	nutrientLevel = 50;

	float opacOffset = 0.1;

	numLayers = 2;
	deadLayer = new GrassTexture("environment/foreground/hill/hill_03.png");
	deadLayer->setPosition(0, screenHeight - deadLayer->getHeight());
	
	grassLayers[0] = new GrassTexture("environment/foreground/hill/hill_02.png");
	grassLayers[0]->setPosition(0, screenHeight - grassLayers[0]->getHeight());

	grassLayers[1] = new GrassTexture("environment/foreground/hill/hill_01.png");
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

	river = new EverRiver(0, screenHeight - 800, &waterLevel);
	
	for(int i=0; i < flowerNum; i++){
		flowers[i] = NULL;
	}
	for(int i=0; i < thornNum; i++){
		thorns[i] = NULL;
	}
	for(int i=0; i < cloudNum; i++){
		clouds[i] = new EverCloud();
	}

	rain = new RainTexture();
}

void EverGround::update(){
	if(*paused == true)
		return;

	// Temperature
	temperature = ofClamp(temperature + (*sunniness - 0.5)/10, 5, 40);

	// Sunniness

	// Wind
	if(wind > 10 || wind < -10)
		wind *= 0.99;
	wind = ofClamp(wind + (*leftWind - *rightWind), -100 , 100);

	tree->swayAmount = wind/6.66f;

	// clouds/rain
	if(abs(cloudLevel) > 20.0f){
		for(int i=0; i<cloudNum; i++){
			clouds[i]->speed = wind/200;
			clouds[i]->setOpacity((cloudLevel-20)/60 * 255);
		}
	}

	cloudLevel += (wind - cloudLevel)/1000.0f + (((abs(wind) - abs(cloudLevel)) > 0) ? (wind-cloudLevel)/300 : 0);
	//printf("wind: %f, Cloud: %f\n", wind, cloudLevel);

	// Nutrients


	// Plants
	*plantType = 3;
	if(*plantType == 0){ // NOthing
		grassHealth = (grassHealth > 0) ? grassHealth - (*sunniness - waterLevel) / 5000.0f : 0;
	}
	else if(*plantType == 1){ // Grass
		grassHealth = (grassHealth < 1) ? grassHealth + (waterLevel - *sunniness) / 2000.0f : 1;
	}
	else if(*plantType == 2){ // Flowers
		addPlants(false);
	}
	else if(*plantType == 3){ // thorns
		addPlants(true);
	}

	river->update();
	makeItRain();

	updateUIBars();
}

void EverGround::makeItRain(){
	rainAmount += 0.1;
	rain->setAmount(rainAmount);
	rain->update();

	waterLevel = ofClamp(waterLevel + rainAmount/300, 0, 100);
	nutrientLevel = ofClamp(nutrientLevel + rainAmount/600 + 0.5, 0, 100);
}

void EverGround::draw(){
	//deadLayer->draw(0);
	//displayManager->addtoLayer(deadLayer, 0);

	river->drawForeground();

	if(grassHealth < 0.5){
		grassLayers[1]->setOpacity(0);
		grassLayers[0]->setOpacity(grassHealth/0.5 * 255);
		deadLayer->draw();
	}
	else{
		grassLayers[0]->setOpacity(255);
		grassLayers[1]->setOpacity((grassHealth-0.5)/0.5 * 255);
	}
	for(int i=0; i<numLayers; i++) {
		grassLayers[i]->draw();
	}

	tree->draw();

	for(int i=0; i<50; i++){
		if(flowers[i] != NULL){
			flowers[i]->draw();
		}
	}

	for(int i=0; i<20; i++){
		if(thorns[i] != NULL){
			thorns[i]->draw();
		}
	}

	rain->draw();
	rain->drawDroplets(0, screenHeight);
}

void EverGround::drawMidground(){
	midgroundTexture->draw();
	river->drawMidground();
	rain->drawMidground();
}

void EverGround::drawBackground(){
	skyTexture->draw();
	drawSun();
	backgroundTexture->draw();
	
	if(cloudLevel > 20.0f){
		for(int i=0; i<cloudNum; i++){
			clouds[i]->draw();
		}
	}
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

void EverGround::addPlants(bool thorn){
	if(thorn && numThorns < 20 && ofRandomuf() < (1 - grassHealth)/100){
		printf("thorns");
		thorns[numThorns] = new EverPlant(ofPoint(ofRandom(screenWidth-400) + 100, screenHeight-ofRandom(150)), true);
		numThorns++;
	}

	else if(!thorn && ofRandomuf() < (grassHealth+1)/100){
		printf("flowers");
		flowers[numFlowers] = new EverPlant(ofPoint(ofRandom(screenWidth-400) + 100, screenHeight-ofRandom(150)), false);
		numFlowers++;
	}
}

void EverGround::setUIBars(EverStats* sun, EverStats* water, EverStats* nutrient, EverStats* temp){
	sunStat = sun;
	waterStat = water;
	nutrientStat = nutrient;
	tempStat = temp;
}

void EverGround::updateUIBars(){
	sunStat->setValue(*sunniness);
	tempStat->setValue((temperature - 5)/35.0f);
	waterStat->setValue(waterLevel/100);
	nutrientStat->setValue(nutrientLevel/100);
}

void EverGround::setControllerPointer(float* lWind, float* rWind, float* sun, float* shaky, int* plant){
	leftWind = lWind;
	rightWind = rWind;
	sunniness = sun;
	shakiness = shaky;
	plantType = plant;
}

void EverGround::setTree(EverTree* tree){
	this->tree = tree;
}


EverGround::~EverGround(void)
{

}