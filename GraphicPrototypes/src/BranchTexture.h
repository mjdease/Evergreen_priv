#pragma once
#include "EverTexture.h"

class BranchTexture : public EverTexture
{
public:
	void draw(ofPoint p1, ofPoint p2);
	void draw(float x1, float y1, float x2, float y2);

	BranchTexture(string src);
	~BranchTexture(void);
};

