#pragma once
#include "../ofMain.h"
#include "EverBranch.h"

class EverTree : public ofNode
{
public:
	ofVec2f* pos;
	ofVec2f* endPos; // Relative to pos

	float angle;

	float height;

	// BRANCH CHILDREN
	vector<EverBranch*> children;

	void addBranch();

	void setPos(ofVec2f);
	void update();
	void draw();

	// CONSTANTS
	static float const MAX_CHILDREN;

	EverTree(void);
	//~EverTree(void);
};

