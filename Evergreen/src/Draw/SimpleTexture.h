#pragma once
#include "EverTexture.h"

class SimpleTexture : public EverTexture
{
public:
	float x, y;

	void setPosition(float x, float y);
	void draw(float offset);
	SimpleTexture(string src);
	~SimpleTexture(void);

private:
};

