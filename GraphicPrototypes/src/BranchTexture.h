#pragma once
#include "EverTexture.h"

class BranchTexture : public EverTexture
{
public:
	void draw(float offset);
	void draw(ofPoint p1, ofPoint p2);
	void setStartEnd(ofPoint start, ofPoint end);
	void setResolution(int resolution);
	void setAmplitude(float amp);
	void setWidths(float* startWidth, float* endWidth);

	BranchTexture(float* startHeight, float* endHeight);
	BranchTexture(string src);
	~BranchTexture(void);
	int resolution;

private:
	float* startWidth;
	float* endWidth;

	float randomOffset;
	float amplitude;
	ofPoint point1, point2;
};

