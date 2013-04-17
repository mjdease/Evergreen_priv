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

	void draw();
	void drawMidground();
	void drawBackground();

	void setTree(EverTree* tree);

	EverGround(int screenHeight);
	~EverGround(void);
private:
	EverFlower* flowers[100];

	EverTree* tree;
	GrassTexture* grassLayers[2];
	GrassTexture* deadLayer;

	int screenHeight;

	SimpleTexture* midgroundTexture;
	SimpleTexture* backgroundTexture;
	SimpleTexture* skyTexture;
};

