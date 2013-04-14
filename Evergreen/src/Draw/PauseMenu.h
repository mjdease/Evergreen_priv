#pragma once
#include "ofMain.h"
#include "EverStats.h"

class PauseMenu
{
public:
	PauseMenu(void);
	~PauseMenu(void);
	
	ofTrueTypeFont fontTitle;
	ofTrueTypeFont fontSubtitle;
	ofTrueTypeFont fontBody;
	
	// text for pause and restart
	char pause[255];
	char restart[255];

	ofVec2f posTreeStatsTitle;
	ofVec2f posEnvStatsTitle;
	ofVec2f posTreeStats;
	ofVec2f posEnvStats;
	
	float sun, water, nutrients, temperature;

	EverStats* eStatsSun;
	EverStats* eStatsWater;
	EverStats* eStatsTemperature;
	EverStats* eStatsNutrients;

	void draw(void);
};