#pragma once
#include "ofMain.h"
#include "EverTexture.h"

class DisplayLayer {

public:
	float offset;
	int index;
	//EverTexture* texture[1000];
	//void addtoDraw(EverTexture* addedTexture);
	ofFbo buffer;
	void begin();
	void end();
	void draw();
	void setOffset(float offset);

	DisplayLayer(int width, int height, int screenHeight);
	~DisplayLayer(void);
private:
	int width, height;
	int screenOffset;
};