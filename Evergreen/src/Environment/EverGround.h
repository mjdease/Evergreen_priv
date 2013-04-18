#pragma once
#include "ofMain.h"
#include "../Draw/GrassTexture.h"
#include "../Tree/EverTree.h"
#include "EverFlower.h"
#include "../DisplayManager.h"
#include "../Draw/SimpleTexture.h"

class EverGround
{
public:

	ofPoint position;

	float health;
	int numLayers;

	int numFlowers;

	void setHealth(float health);

	void addFlowers();
	
	void update();

	void draw();
	void drawMidground();
	void drawBackground();

	void setControllerPointer(float* lWind, float* rWind, float* sun, float* shaky, int* plant);

	void setTree(EverTree* tree);

	EverGround(int screenHeight, int screenWidth);
	~EverGround(void);
private:
	float temperature;

	float* leftWind;
	float* rightWind;
	float* sunniness;
	float* shakiness;
	int* plantType;

	EverFlower* flowers[100];

	EverTree* tree;
	GrassTexture* grassLayers[2];
	GrassTexture* deadLayer;

	int screenHeight, screenWidth;

	SimpleTexture* midgroundTexture;
	SimpleTexture* backgroundTexture;
	SimpleTexture* skyTexture;

	void drawSun();
};

