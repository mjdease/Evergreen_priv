#pragma once
#include "ofMain.h"
#include "EverTexture.h"

class Layer {

public:
	float offset;
	int index;
	EverTexture* texture[1000];
	void addtoDraw(EverTexture* addedTexture);
	void draw();
	void setOffset(float offset);

	Layer(void);
	~Layer(void);

};