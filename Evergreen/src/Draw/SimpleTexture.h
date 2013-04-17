#pragma once
#include "EverTexture.h"

class SimpleTexture : public EverTexture
{
public:
	float x, y;
	int width, height;
	
	void setPosition(float x, float y);
	void setSize(int width, int height);
	void draw();
	SimpleTexture(string src);
	~SimpleTexture(void);
};

