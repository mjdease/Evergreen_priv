#pragma once
#include "../ofMain.h"
#include "EverBranch.h"
#include "../DisplayManager.h"

class EverTree
{
public:
	static float const MAX_CHILDREN;
	float GROWTH_RATE;
	static ofVec3f const Y_DIRECTION, X_DIRECTION;
	static const string TEXTURE_SRC;
	static const float BRANCH_SEPERATION;
	float birthRate;
	float startWidth, endWidth;
	DisplayManager* displayManager;
	float attachPointProgress;
	bool attachPointSide;

	ofVec3f position;
	ofVec3f endPosition; // Relative to pos
	ofVec3f direction;
	BranchTexture* texture;

	//ofMatrix4x4 directionMatrix;
	ofMatrix4x4 swayMatrix;
	float swayAmount;
	float length;
	float time;

	// BRANCH CHILDREN
	//vector<EverBranch*> children;
	EverBranch* branch[10];
	int numChildren;

	void newChild();

	void update();
	void draw();
	void sway();
	void grow();
	void reproduce();

	void setDirection();
	void setSway(float sway);
	
	void setPosition(ofVec2f);

	EverTree(DisplayManager* manager);
	//~EverTree(void);
};

