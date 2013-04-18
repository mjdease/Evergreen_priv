#include "EverStats.h"

void EverStats::setPosition(ofPoint pos){
	this->pos = pos;
}

void EverStats::resetPosition(){
	this->pos = origPosition;
}

void EverStats::setValue(float val){
	stat = val;
}

void EverStats::draw(void) {
	ofSetColor(barColor);
	ofRect(pos.x + 3, pos.y + 3, stat * barWidth, barHeight);
	
	ofEnableAlphaBlending();
		ofSetColor(255);
		barShell.draw(pos.x, pos.y);
		statIcon.draw(pos.x - 40.0, pos.y);
	ofDisableAlphaBlending();
}

EverStats::EverStats(string icon, float statistic, ofColor color, ofPoint pos)
{
	barWidth = 250.0;
	barHeight = 30.0;
	barShell.loadImage("ui/barShell.png");
	
	statIcon.loadImage(icon);
	this->pos = pos;
	this->origPosition = pos;
	stat = statistic;
	barColor = color;
}


EverStats::~EverStats(void)
{
}