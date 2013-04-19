#pragma once
#include "ofMain.h"
#include "EverStats.h"
#include <ctime>

class PauseMenu
{
public:
	void toggle();
	void show();
	void hide();
	void setBars(EverStats* sun, EverStats* water, EverStats* nutrient, EverStats* temp);
	void setStats(clock_t* time, int* branches, float* health);

	float* getPositionPointer();

	void draw(void);

	bool pressButton();
	void scroll();

	PauseMenu(void);
	~PauseMenu(void);

private:
	int width, height;

	float menuX, destMenuX;
	float displayX; // For the display manager and how much to scale
	
	ofTrueTypeFont fontTitle;
	ofTrueTypeFont fontSubtitle;
	ofTrueTypeFont fontBody;
	
	// text for pause and restart
	char pause[255];
	char restart[255];

	ofPoint posTreeStatsTitle;
	ofPoint posEnvStatsTitle;
	ofPoint posTreeStats;
	ofPoint posEnvStats;
	
	bool menuDrawn;

	EverStats* eStatsSun;
	EverStats* eStatsWater;
	EverStats* eStatsTemperature;
	EverStats* eStatsNutrients;

	enum highlight_t {CONTINUE, RESTART};
	highlight_t highlighted;

	clock_t* startTime;
	int* numBranches;
	float* treeHealth;
};