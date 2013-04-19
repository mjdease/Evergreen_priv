#pragma once
#include "../Draw/SimpleTexture.h"

class EverLeaf
{
public:
	void update();
	void draw();

	void setPosition(float length);

	EverLeaf(int leafType);
	~EverLeaf(void);

private:
	float width, height;
	float oWidth, oHeight;

	float length;

	SimpleTexture* drawLeaf;

	static SimpleTexture* leaf1;
	static SimpleTexture* leaf2;
	static SimpleTexture* leaf3;
	static SimpleTexture* leaf4;
	static SimpleTexture* leaf5;
	static SimpleTexture* leaf6;

	void loadImages(int leafType);
};

