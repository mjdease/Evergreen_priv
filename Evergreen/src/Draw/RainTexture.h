#pragma once
#include "EverTexture.h"

class RainTexture
{
public:
	float x, y;
	int width, height;
	
	void setPosition(float x, float y);
	void setSize(int width, int height);
	void setAmount(float amount);
	void update();
	void draw();
	void drawMidground();
	void drawDroplets(int x, int y);
	RainTexture();
	~RainTexture(void);

private:
	int frame;
	int dropletHeight;
	float rainAmount;
	EverTexture* rain[6];
	EverTexture* droplets[3];

	void loadImages();
};

