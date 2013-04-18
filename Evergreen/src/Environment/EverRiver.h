#pragma once
#include "../ofMain.h"
#include "../Draw/EverTexture.h"
#include "../DisplayManager.h"

class EverRiver
{
public:
	EverRiver(float x, float y, float* water);
	void update();

	void drawForeground();
	void drawMidground();
	~EverRiver(void);

private:
	int frameNum;
	int frameDir;

	float x, y;
	float* waterLevel;
	ofPoint fgPosition;
	ofPoint mgPosition;
	
	EverTexture* fgRiver1[4];
	EverTexture* fgRiver2[4];
	EverTexture* fgRiver3[4];
	EverTexture* fgRiver4[4];

	EverTexture** drawnFg;

	float opacities[4];

	EverTexture* mgRiver[4];

	void loadImages();
};

