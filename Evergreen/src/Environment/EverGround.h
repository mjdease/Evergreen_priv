#pragma once
#include "ofMain.h"
#include "../Draw/GrassTexture.h"
#include "EverFlower.h"
#include "../DisplayManager.h"

class EverGround
{
public:
	DisplayManager* displayManager;

	ofPoint position;

	float health;
	int numLayers;
	GrassTexture* grassLayers[2];
	GrassTexture* deadLayer;

	int numFlowers;
	EverFlower* flowers[100];

	void setHealth(float health);

	void addFlowers();
	void draw();

	EverGround(DisplayManager* manager);
	~EverGround(void);
};

