#pragma once
#include "ofMain.h"

class EverStats
{
public:
	ofImage barShell;

	float barWidth;
	float barHeight;

	ofImage statIcon;
	float stat;
	ofVec2f pos;
	ofColor barColor;

	EverStats(string, float, ofColor, ofVec2f);
	~EverStats(void);

	void draw(void);
};

