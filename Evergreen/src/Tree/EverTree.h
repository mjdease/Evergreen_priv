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

	float TREE_HEALTH;
	float swayAmount;

	EverTree();
	~EverTree(void);

private:
	static const int MAX_CHILDREN;
	static const string TEXTURE_SRC;
	int depth;
	int limbDepth;

	float trunkLength;

	vector <EverBranch*> children;
	int numChildren;
	float birthRate;

	void reproduce();
	float swayAngle;
	BranchTexture* texture;
	float startWidth, endWidth;
};