#pragma once
#include "../ofMain.h"
#include "../Draw/BranchTexture.h"
#include "../DisplayManager.h"

class EverBranch
{
public:
	static const ofVec3f X_DIRECTION;
	static const ofVec3f Y_DIRECTION;
	static const float CHILD_DECAY;
	static const float GROWTH_DECAY;
	static const float MAX_BEND_DECAY;
	static const float MIN_BEND_DECAY;
	static const float SWAY_DECAY;
	static const float BIRTHRATE_DECAY;
	static const int BRANCH_SEPERATION;
	static const float BASE_ANGLE;
	static const string TEXTURE_SRC;
	float MAX_CHILD_BEND;
	float MIN_CHILD_BEND;
	float MAX_CHILDREN;
	float BIRTHRATE;
	float GROWTH_RATE;
	float SWAY_AMOUNT;
	float ATTACH_POINT;
	bool MAIN_LIMB;

	EverBranch* parent;
	vector<EverBranch*> children;
	int numChildren;
	BranchTexture* texture;
	void newChild();
	DisplayManager* displayManager;

	bool clockwise;
	float weight;
	float startWidth, endWidth;
	ofPoint position;
	ofPoint endPosition;
	ofVec3f direction;
	float length;
	float angle;
	ofMatrix4x4 branchBaseMatrix;
	ofMatrix4x4 adjustmentMatrix;
	ofMatrix4x4 baseMatrix; // For angle relative to the parent
	ofMatrix4x4 rotationMatrix; // For angle of the parent
	ofMatrix4x4 swayMatrix; // For angle of the sway animation
	
	void update();
	void draw();
	void draw(float offset);
	void grow();
	void adjustLimb();
	void reproduce();
	
	void setPosition(ofVec2f position);
	void setRotationMatrix(ofMatrix4x4 rotation);
	void setSwayAmount(float sway);
	void setBranchAngle(float angle);
	void adjustGrowthRate(float adjust);
	
	EverBranch(void);
	EverBranch(DisplayManager* manager);
	EverBranch(EverBranch* parent);
	void init();
	float time;
};