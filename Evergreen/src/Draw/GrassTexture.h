#pragma once
#include "EverTexture.h"

class GrassTexture : public EverTexture
{
public:
	float x, y;

	void setPosition(float x, float y);
	void draw();
	GrassTexture(string src);
	~GrassTexture(void);

private:
};

