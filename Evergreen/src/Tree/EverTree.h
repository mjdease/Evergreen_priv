#pragma once
#include "ofMain.h"
#include "EverBranch.h"

class EverTree
{
public:
	void update();
	void draw();

	ofPoint position;

	void setPosition(float x, float y);
	void setSway(float sway);
	float wind;

	void getEnvPointers(float* sun, float* water, float* nutrient, float* temperature);

	float TREE_HEALTH;

	int numBranches;

	EverTree();
	~EverTree(void);

private:
	static const int MAX_CHILDREN;
	static const string TEXTURE_SRC;
	int depth;
	int limbDepth;

	float trunkLength;

	float swayAmount;

	vector <EverBranch*> children;
	int numChildren;
	float birthRate;

	void reproduce();
	float swayAngle;
	BranchTexture* texture;
	float startWidth, endWidth;

	float* sun;
	float* water;
	float* nutrient;
	float* temperature;
};