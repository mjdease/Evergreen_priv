#include "EverStats.h"

EverStats::EverStats(string icon, float statistic, ofColor color, ofVec2f pos)
{
	barWidth = 250.0;
	barHeight = 30.0;
	barShell.loadImage("ui/barShell.png");
	
	statIcon.loadImage(icon);
	this->pos = pos;
	stat = statistic;
	barColor = color;
}


EverStats::~EverStats(void)
{
}


void EverStats::draw(void) {
	ofSetColor(barColor);
	ofRect(pos.x + 3, pos.y + 3, stat * 0.01 * barWidth, barHeight);
	
	ofEnableAlphaBlending();
		ofSetColor(255);
		barShell.draw(pos.x, pos.y);
		statIcon.draw(pos.x + 260.0, pos.y);
	ofDisableAlphaBlending();
}