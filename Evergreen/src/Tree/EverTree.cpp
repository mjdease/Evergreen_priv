#include "EverTree.h"
const int EverTree::MAX_CHILDREN= 3;
DisplayLayer* EverTree::layer = NULL;
const string EverTree::TEXTURE_SRC = "bark.bmp";

void EverTree::reproduce(){
	if(numChildren < MAX_CHILDREN && ofRandomuf() < birthRate){
		EverBranch* branch = new EverBranch();
		children.push_back(branch);
		numChildren++;
		if(limbDepth < 1)
			limbDepth = 1;
	}
}

void EverTree::update(){
	trunkLength += (TREE_HEALTH/100.0f * 500.0f - trunkLength)/10000.0f;

	
	for(int i=0; i<numChildren; i++){
		children[i]->update();
	}

	swayAngle *= 0.5f;
	swayAngle += sinf(ofGetFrameNum() * (swayAmount) / 300.0f) * (swayAmount*2.0f) / 10.0f;

	reproduce();

	texture->setStartEnd(ofPoint(0,0), ofPoint(0,trunkLength));

	//printf("Limb Depth: %d\n", limbDepth);
}

void EverTree::draw(){
	ofPushMatrix();

	ofTranslate(position);
	ofRotate(180 + swayAngle);
	/*ofSetColor(0);
	ofLine(0,0,0,trunkLength);
	ofCircle(0,0,3);*/
	//layer->addtoDraw(texture);
	texture->draw(0);

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


EverTree::EverTree(DisplayLayer* layer)
{
	startWidth = endWidth = 10;
	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(1);

	this->layer = layer;
	TREE_HEALTH = 100.0f;
	depth = 0;
	limbDepth = 0;
	trunkLength = 0;
	birthRate = 0.001f;
	numChildren = 0;
	swayAmount = 1.0f;
	EverBranch::setPointers(&TREE_HEALTH, &depth, &limbDepth, &numChildren, &children, &swayAmount, layer);
}

EverTree::~EverTree(void)
{
}
