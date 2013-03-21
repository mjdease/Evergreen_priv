#include "BranchTexture.h"

BranchTexture::BranchTexture(string src):EverTexture(src)
{
	resolution = 10;
	randomOffset = ofRandom(0, 100);
	loadTexture(src);

	// offset must be higher than amplitude
	amplitude = 25;
}

BranchTexture::BranchTexture(float* startWidth, float* endWidth):EverTexture(){
	this->startWidth = startWidth;
	this->endWidth = endWidth;
	randomOffset = ofRandomuf();
	amplitude = 25;
	resolution = 10;
}

void BranchTexture::draw(float offset){
	draw(ofPoint(point1.x, point1.y + offset), ofPoint(point2.x, point2.y + offset));
}

void BranchTexture::draw(ofPoint p1, ofPoint p2){
	float angle = ofRadToDeg(atan2f((p2.y-p1.y),(p2.x-p1.x)));
	ofVec2f delta = p2-p1;
	float widthDelta = *endWidth/2-*startWidth/2;
	float length = delta.length();

	ofPoint q1, q2, q3, q4; // start Top, start bottom, end top, end bottom

	for(float i=0; i <= resolution; i++){
		float percent = i/resolution;
		float wave = amplitude*ofNoise(percent * 5, randomOffset);

		if(i == 0){
			q1 = ofPoint(percent * length, -*startWidth/2-widthDelta*percent);
			q2 = ofPoint(percent * length, *startWidth/2+widthDelta*percent);
			continue;
		}
		
		q3 = ofPoint(percent * length, -*startWidth/2 - (widthDelta) * percent + (1-percent)*wave);
		q4 = ofPoint(percent * length, *startWidth/2 + (widthDelta) * percent + (1-percent)*wave);
		
		
		ofPushMatrix();
			ofTranslate(p1.x, p1.y);
			ofRotate(angle);
			drawTexture(q2, q4, q1, q3);
		ofPopMatrix();

		q1 = q3;
		q2 = q4;
	}
}

void BranchTexture::setStartEnd(ofPoint start, ofPoint end) {
	point1 = start;
	point2 = end;
}

void BranchTexture::setResolution(int resolution) {
	this->resolution = resolution;
}

void BranchTexture::setAmplitude(float amp){
	amplitude = amp;
}

void BranchTexture::setWidths(float* startWidth, float* endWidth){
	this->startWidth = startWidth;
	this->endWidth = endWidth;
}

BranchTexture::~BranchTexture(void)
{
}