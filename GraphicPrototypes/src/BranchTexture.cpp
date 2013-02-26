#include "BranchTexture.h"


BranchTexture::BranchTexture(string src):EverTexture(src)
{
}

void BranchTexture::draw(ofPoint p1, ofPoint p2){
	float angle = ofRadToDeg(atan2f((p2.y-p1.y),(p2.x-p1.x)));

	EverTexture::draw(p2.x,p2.y ,100, 100, angle);
}

void BranchTexture::draw(float x1, float y1, float x2, float y2){
	float angle = ofRadToDeg(atan2f((y2-y1),(x2-x1)));
	EverTexture::draw(x2,y2 ,100, 100, angle);
}


BranchTexture::~BranchTexture(void)
{
}
