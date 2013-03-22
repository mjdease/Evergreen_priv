#pragma once
#include "ofMain.h"
#include "../Draw/GrassTexture.h"
#include "../Tree/EverTree.h"
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

	EverTree* tree;

	void setHealth(float health);

	void addFlowers();
	void draw();

	void setTree(EverTree* tree);

	EverGround(DisplayManager* manager);
	~EverGround(void);
};

