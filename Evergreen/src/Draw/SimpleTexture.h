#pragma once
#include "EverTexture.h"

class SimpleTexture : public EverTexture
{
public:
	float x, y;
	int width, height;
	bool show;
	
	void setPosition(float x, float y);
	void setSize(int width, int height);
	void draw();
	void draw(float width, float height);
	SimpleTexture(string src);
	~SimpleTexture(void);
};

