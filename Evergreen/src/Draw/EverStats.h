#pragma once
#include "ofMain.h"

class EverStats
{
public:
	void resetPosition();
	void setPosition(ofPoint pos);
	void setValue(float val);

	EverStats(string, float, ofColor, ofPoint);
	~EverStats(void);
	
	void draw(void);
	void drawPaused(void);

private:
	ofImage barShell;

	float barWidth;
	float barHeight;

	ofImage statIcon;
	float stat;
	ofPoint pos;
	ofColor barColor;

	ofPoint origPosition;
};

