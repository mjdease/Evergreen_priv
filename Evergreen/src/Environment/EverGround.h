#pragma once
#include "ofMain.h"
#include "../Draw/GrassTexture.h"
#include "../Tree/EverTree.h"
#include "EverPlant.h"
#include "EverRiver.h"
#include "EverCloud.h"
#include "../DisplayManager.h"
#include "../Draw/SimpleTexture.h"
#include "../Draw/EverStats.h"
#include "../Draw/RainTexture.h"

class EverGround
{
public:

	ofPoint position;

	float grassHealth;
	int numLayers;

	void setHealth(float grassHealth);

	int getWeather();
	
	void update();

	void draw();
	void drawMidground();
	void drawBackground();

	void setUIBars(EverStats* sun, EverStats* water, EverStats* nutrient, EverStats* temp);
	void setControllerPointer(float* lWind, float* rWind, float* sun, float* shaky, int* plant);

	void setTree(EverTree* tree);

	EverGround(int screenHeight, int screenWidth, bool* paused);
	~EverGround(void);
private:
	bool* paused;

	// Send to tree
	float temperaturePercent;
	float waterPercent;
	float nutrientPercent;
	float sunPercent;

	// Sunniness, water, nutrient, temperature
	float temperature;
	float wind;
	float waterLevel;
	float nutrientLevel;
	float sunLevel;

	float* leftWind;
	float* rightWind;
	float* sunniness;
	float* shakiness;
	int* plantType;
	
	EverPlant* flowers[50];
	EverPlant* thorns[20];

	EverTree* tree;
	GrassTexture* grassLayers[2];
	GrassTexture* deadLayer;

	EverCloud* clouds[30];

	int screenHeight, screenWidth;

	SimpleTexture* midgroundTexture;
	SimpleTexture* backgroundTexture;
	SimpleTexture* skyTexture;
	
	EverStats* sunStat;
	EverStats* waterStat;
	EverStats* nutrientStat;
	EverStats* tempStat;
	void updateUIBars();

	EverRiver* river;

	int numFlowers, numThorns;

	void addPlants(bool thorn);

	void drawSun();

	float overcastLevel;
	RainTexture* rain;
	float rainLevel;
	void makeItRain();
	SimpleTexture* stormCloudLeft;
	SimpleTexture* stormCloudRight;
};

