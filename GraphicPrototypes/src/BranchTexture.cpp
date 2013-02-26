#include "BranchTexture.h"


BranchTexture::BranchTexture(string src):EverTexture(src)
{
	resolution = 100;
	amplitude = 9;
}

void BranchTexture::draw(ofPoint p1, ofPoint p2){
	float angle = ofRadToDeg(atan2f((p2.y-p1.y),(p2.x-p1.x)));
	
	ofSetColor(255,100,100);
	ofFill();
	// ofRect(p1.x,p1.y,p2.x-p1.x,p2.y-p1.y);
	
	ofVec2f vect = p2 - p1;
	float pX = 0;
	float pY = 0;

	for(float i = 0; i <= resolution; i++) {
		float x = i/resolution;
		

		ofVec2f temp = vect * x;

		float p2X = temp.x + p1.x;
		float p2Y = temp.y + p1.y + amplitude*sinf(x*PI*2);
		
		if(i > 0)
			ofLine(pX, pY, p2X, p2Y);
		//ofCircle(temp.x + p1.x,temp.y + p1.y + amplitude*sinf(x*PI*2), 2);

		pX = p2X;
		pY = p2Y;
	}

	// EverTexture::draw(p2.x,p2.y ,100, 100, angle);
}

void BranchTexture::setResolution(int resolution) {
	this->resolution = resolution;
}

void BranchTexture::draw(float x1, float y1, float x2, float y2){
	float angle = ofRadToDeg(atan2f((y2-y1),(x2-x1)));
	EverTexture::draw(x2,y2 ,100, 100, angle);
}


BranchTexture::~BranchTexture(void)
{
}
