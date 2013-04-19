#include "EverTree.h"
const int EverTree::MAX_CHILDREN= 3;
const string EverTree::TEXTURE_SRC = "bark.bmp";

void EverTree::reproduce(){
	if(numChildren < MAX_CHILDREN && ofRandomuf() < birthRate){
		EverBranch* branch = new EverBranch();
		branch->setStartWidth(&endWidth);
		children.push_back(branch);
		numChildren++;
		if(limbDepth < 1)
			limbDepth = 1;
	}
}

void EverTree::update(){
	// Health
	float targetHealth = 0;
	if(*sun > 0.1 && *water > 0.1 && *nutrient > 0.1)
		targetHealth = (*sun + *water + *nutrient)/3 *100;
	else
		targetHealth = (*sun + *water + *nutrient)/5 * 100;

	// Set all the other values
	trunkLength += (TREE_HEALTH/100.0f * 350.0f - trunkLength)/10000.0f;
	startWidth = trunkLength/ 5 * (TREE_HEALTH/70 + 1);
	if(numChildren == 0){
		endWidth = 1;
	}
	else{
		endWidth = startWidth/2;
	}
	
	for(int i=0; i<numChildren; i++){
		children[i]->update();
	}

	swayAngle *= 0.9f;
	swayAngle += sinf(ofGetFrameNum() * (swayAmount) / 300.0f) * (swayAmount*2.0f) / 7.0f + (swayAmount*2.0f) / 7.0f;

	reproduce();

	texture->setStartEnd(ofPoint(0,0), ofPoint(0,trunkLength));

	//printf("Limb Depth: %d\n", limbDepth);
}

void EverTree::draw(){
	ofPushMatrix();

	ofTranslate(position);
	ofRotate(180 + swayAngle);
	texture->draw(0);
	/*
	ofSetColor(0);
	ofLine(0,0,0,trunkLength);
	ofCircle(0,0,3);
	*/
	//layer->addtoDraw(texture);
	//texture->draw(0);

	ofTranslate(0,trunkLength, 0);
	for(int i=0; i<numChildren; i++){
		ofPushMatrix();
		children[i]->draw();
		ofPopMatrix();
	}

	ofPopMatrix();
}

void EverTree::setPosition(float x, float y){
	position.x = x;
	position.y = y;
}

void EverTree::getEnvPointers(float* sun, float* water, float* nutrient, float* temperature){
	this->sun = sun;
	this->water = water;
	this->nutrient = nutrient;
	this->temperature = temperature;
}


EverTree::EverTree()
{
	startWidth = 3;
	endWidth = 1;
	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(1);

	TREE_HEALTH = 100.0f;
	depth = 0;
	limbDepth = 0;
	trunkLength = 0;
	birthRate = 0.001f;
	numChildren = 0;
	swayAmount = 1.0f;
	EverBranch::setPointers(&TREE_HEALTH, &depth, &limbDepth, &numChildren, &children, &swayAmount);
}

EverTree::~EverTree(void)
{
}
