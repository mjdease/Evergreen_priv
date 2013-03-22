#pragma once
#include "../ofMain.h"
#include "../Draw/EverTexture.h"
#include "../DisplayManager.h"

class EverFlower : public EverTexture
{
public:
	ofPoint position;
	ofPoint MAX_SIZE;
	DisplayManager display;
	ofImage flowerImg;
	EverTexture* flower;

	float flower_width, flower_height;

	EverFlower(ofPoint position);
	void draw(float height);
	~EverFlower(void);
};

