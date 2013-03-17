#include "BranchTexture.h"

BranchTexture::BranchTexture(string src):EverTexture(src)
{
	branchWidth = 50;
	resolution = 10;
	randomOffset = ofRandom(0, 100);
	ofLoadImage(texture, src);
	this->src = src;

	// offset must be higher than amplitude
	amplitude = 25;
	offset = 30;
}

void BranchTexture::draw(ofPoint p1, ofPoint p2){
	float angle = ofRadToDeg(atan2f((p2.y-p1.y),(p2.x-p1.x)));
	
	ofTexture texture;
	ofLoadImage(texture,src);

	ofSetColor(255,100,100);
	ofFill();
	
	ofVec2f mouseline = p2 - p1;
	float pX = 0;
	float pY = 0;
	float pY_mouse = 0;

	for(float i = 0; i <= resolution; i++) {
		
		float percent = i/resolution;
		
		ofVec2f temp = mouseline * percent;

		float pX2 = temp.length();

		float wave = amplitude*ofNoise(percent*5 + randomOffset);
		float pY2 = wave;
		float pY2_mouse = 0;
		
		float height1 = abs(pY-pY_mouse);
		float height2 = abs(pY2-pY2_mouse);
		float delta = height2-height1;

		ofSetColor(255);

		ofPushMatrix();
			ofTranslate(p1.x, p1.y);
			ofRotate(angle);

			texture.bind();

			// texture coordinates go CW
			glBegin(GL_QUADS);
				
				glVertex3f(pX, -height1 + branchWidth, 0);
				glTexCoord2f(width, height);
				
				glVertex3f(pX, -height1, 0);
				glTexCoord2f(0, height);
				
				glVertex3f(pX2, -height2, 0);
				glTexCoord2f(0.0f, 0.0f);
				
				glVertex3f(pX2, -height2 + branchWidth, 0);
				glTexCoord2f(width, 0.0f);

			glEnd();

			texture.unbind();

		ofPopMatrix();
		pX = pX2;
		pY = pY2;
		pY_mouse = pY2_mouse;
	}
	
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