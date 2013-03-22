#pragma once
#include "ofMain.h"
#include "GrassTexture.h"
#include "DisplayManager.h"

class EverGround
{
public:
	DisplayManager* displayManager;

	ofPoint position;

	float health;
	int numLayers;
	GrassTexture* grassLayers[2];
	GrassTexture* deadLayer;

	void setHealth(float health);
	void draw();

	EverGround(void);
	~EverGround(void);
};

