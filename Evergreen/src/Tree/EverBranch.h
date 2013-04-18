#pragma once
#include "../ofMain.h"
#include "../Draw/BranchTexture.h"
#include "../DisplayManager.h"

class EverBranch
{
public:
	void update();
	void draw();

	void addWind();
	
	EverBranch();
	EverBranch(EverBranch* parent);
	~EverBranch(void);

	static void setPointers(float* TreeHealth,
		int* depth,
		int* limbDepth,
		int* rootSiblings,
		vector <EverBranch*>* siblingBranches,
		float* swayAmount);

	static int* GlobalDepth;
	static int* GlobalLimbDepth;
	static float* TreeHealth;

protected:
	// Drawing
	float length;
	float angle; // Displayed angle
	float attachPoint;
	float startWidth, endWidth;

	// Calculations
	float baseAngle;
	float swayAngle;

	float maxAngle, minAngle;
	float angleMultiplier;

	float globalAngle;
	int depth;
	int limbDepth;

	float birthRate;
	float maxChildren;
	
	EverBranch* parent;
	vector <EverBranch*> children;
	int numChildren;
	static vector <EverBranch*>* siblings; // only to be used by root branches
	static int* rootSiblingNum;
	
private:
	static const float BIRTH_DECAY;
	static const float CHILD_DECAY;
	static const int MAX_DEPTH;
	static const string TEXTURE_SRC;
	static float* swayAmount;
	static const float WIDTH_DECAY;

	BranchTexture* texture;

	// Update
	void updateAngle();
	void sway();
	void grow();
	void reproduce();
	void newChild();

	static float convertAngle(float angle);
};

