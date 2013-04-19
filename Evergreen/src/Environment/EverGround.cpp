#include "EverGround.h"

#define cloudNum 30
#define flowerNum 50
#define thornNum 20


int EverGround::getWeather(){
	return ofClamp(abs(wind)*2, 0, 100);
}

EverGround::EverGround(int screenHeight, int screenWidth, bool* paused) {
	this->paused = paused;
	grassHealth = 1;
	numFlowers = numThorns = 0;

	temperature = 20;
	wind = 10;
	waterLevel = 100;
	nutrientLevel = 100;

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

	stormCloudLeft = new SimpleTexture("environment/background/stormcloudLeft.png");
	stormCloudLeft->setPosition(-screenWidth, -420);
	stormCloudRight = new SimpleTexture("environment/background/stormcloudRight.png");
	stormCloudRight->setPosition(screenWidth, -420);
}

void EverGround::update(){
	if(*paused == true)
		return;

	// Sunniness
	sunLevel = ofClamp(*sunniness/2 + 0.5 - overcastLevel, 0, 1);

	// Temperature
	temperature = ofClamp(temperature + (sunLevel - (temperature-5)/35)/5, 5, 40);
	temperaturePercent =  (temperature-5)/35;

	// Nutrients
	nutrientLevel = ofClamp(nutrientLevel - (numFlowers+numThorns + 3)/200.0f, 0, 100);

	// Water Level
	waterLevel = ofClamp(waterLevel - (sunPercent)/10, 0, 100);

	// Wind
	if(abs(*leftWind - *rightWind) < 0.05 || ((*leftWind - *rightWind) > 0 && wind < 0) || ((*leftWind - *rightWind) < 0 && wind > 0) )
		wind *= 0.98;

	wind = ofClamp(wind + (*leftWind - *rightWind)/2, -100 , 100);
		
	tree->setSway(wind/13.0f);

	// clouds/rain
	if(abs(wind) > 10.0f+temperaturePercent*10){
		for(int i=0; i<cloudNum; i++){
			clouds[i]->speed = wind/50;
			clouds[i]->setOpacity((abs(wind)-10)/20.0f * 255);// At 30 they become fully opaque
			clouds[i]->update();
		}
	}

	// if wind > 15. Scaled from 15 - 35
	overcastLevel = ofClamp((abs(wind)-15-temperaturePercent*10)/20, 0 ,1);

	// 25 the rain will start to come, at 50 the light rain will max, at 75 the heavy rain will max
	rainLevel = ofClamp((abs(wind)-25-temperaturePercent*10)/50 * 100, 0, 100);

	if(abs(wind) > 50.0f+temperaturePercent*10){
		stormCloudLeft->show = true;
		stormCloudRight->show = true;
		if(wind > 0)
			stormCloudLeft->x += (-100 - stormCloudLeft->x)/500.0f;
		else if(wind < 0)
			stormCloudRight->x += (100 - stormCloudRight->x)/500.0f;
	}
	else{
		if(stormCloudLeft->x != -screenWidth){
			stormCloudLeft->x += (-100 - stormCloudLeft->x)/500.0f;
			stormCloudLeft->opacity -= 2;
			if(stormCloudLeft->opacity < 0){
				stormCloudLeft->x = -screenWidth;
				stormCloudLeft->opacity = 255;
				stormCloudLeft->show = false;
			}
		}
		if(stormCloudRight->x != screenWidth){
			stormCloudRight->x += (100 - stormCloudRight->x)/500.0f;
			stormCloudRight->opacity -= 2;
			if(stormCloudRight->opacity < 0){
				stormCloudRight->x = screenWidth;
				stormCloudRight->opacity = 255;
					stormCloudRight->show = false;
			}
		}
	}

	// Plants
	if(*plantType == 0){ // NOthing
		grassHealth = (grassHealth > 0) ? grassHealth - 1 / (*sunniness + waterLevel + 1) / 500.0f : 0;
	}
	else if(*plantType == 1){ // Grass
		grassHealth = (grassHealth < 1) ? grassHealth + (waterLevel - *sunniness) / 2000.0f : 1;
	}
	else if(*plantType == 2){ // Flowers
		addPlants(false);
		grassHealth = (grassHealth > 0) ? grassHealth - (*sunniness - waterLevel) / 7000.0f : 0;
	}
	else if(*plantType == 3){ // thorns
		addPlants(true);
		grassHealth = (grassHealth > 0) ? grassHealth - (*sunniness - waterLevel) / 7000.0f : 0;
	}

	river->update();

	if(rainLevel > 0)
		makeItRain();

	updateUIBars();
}

void EverGround::makeItRain(){
	rain->setAmount(rainLevel);
	rain->update();

	waterLevel = ofClamp(waterLevel + rainLevel/300, 0, 100);
	nutrientLevel = ofClamp(nutrientLevel + rainLevel/600, 0, 100);
}

void EverGround::draw(){
	//deadLayer->draw(0);
	//displayManager->addtoLayer(deadLayer, 0);

	river->drawForeground();
	if(grassHealth < 0.5){
		grassLayers[1]->setOpacity(0);
		grassLayers[0]->setOpacity(grassHealth*2 * 255);
		deadLayer->draw();
		grassLayers[0]->draw();
	}
	else{
		grassLayers[0]->setOpacity(255);
		grassLayers[1]->setOpacity((grassHealth-0.5)*2 * 255);
		
		grassLayers[0]->draw();
		grassLayers[1]->draw();
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
	
	if(rainLevel > 0){
		rain->draw();
		rain->drawDroplets(0, screenHeight);
	}
}

void EverGround::drawMidground(){
	midgroundTexture->draw();
	river->drawMidground();
	rain->drawMidground();
}

void EverGround::drawBackground(){
	skyTexture->draw();
	drawSun();
	ofEnableAlphaBlending();
	if(overcastLevel > 0){
		ofSetColor(200, 200, 200, ofClamp(overcastLevel * 230, 0, 200));
		ofRect(0,0, screenWidth, screenHeight);
	}
	
	if(stormCloudLeft->show == true || stormCloudRight->show == true){
		stormCloudLeft->draw();
		stormCloudRight->draw();
	}
	backgroundTexture->draw();
	
	if(abs(wind) > 10 + temperaturePercent*10){
		for(int i=0; i<cloudNum; i++){
			clouds[i]->draw();
		}
	}
	ofDisableAlphaBlending();
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
	if(thorn && numThorns < 20 && ofRandomuf() < (1 - grassHealth)/70){
		printf("thorns");
		thorns[numThorns] = new EverPlant(ofPoint(ofRandom(screenWidth-400) + 100, screenHeight-ofRandom(150)), true);
		numThorns++;
	}

	else if(!thorn && ofRandomuf() < (grassHealth+1)/70){
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
	sunStat->setValue(sunLevel);
	tempStat->setValue((temperature - 5)/35.0f);
	waterStat->setValue(waterLevel/100);
	nutrientStat->setValue(nutrientLevel/100);

	// temperatue Percent
	waterPercent = waterLevel/100;
	nutrientPercent = nutrientLevel/100;
	sunPercent = sunLevel;
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
	tree->getEnvPointers(&sunPercent, &waterPercent, &nutrientPercent, &temperaturePercent);
}


EverGround::~EverGround(void)
{

}