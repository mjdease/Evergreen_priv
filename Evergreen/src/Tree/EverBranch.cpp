// effective c++ book
#include "EverBranch.h"

const ofVec3f EverBranch::X_DIRECTION(1,0,0);
const ofVec3f EverBranch::Y_DIRECTION(0,1,0);
const float EverBranch::CHILD_DECAY = 0.7f;
const float EverBranch::GROWTH_DECAY = 0.6f;
const float EverBranch::BIRTHRATE_DECAY = 0.7f;
const float EverBranch::MAX_BEND_DECAY = 0.9f;
const float EverBranch::MIN_BEND_DECAY = 0.9f;
const float EverBranch::SWAY_DECAY = 0.8f;
const float EverBranch::BASE_ANGLE = 90.0f;
const int EverBranch::BRANCH_SEPERATION = 7;
const string EverBranch::TEXTURE_SRC = "bark.bmp";

EverBranch::EverBranch(void): parent(NULL), MAX_CHILDREN(5), GROWTH_RATE(0.05f), BIRTHRATE(0.0025f), MAIN_LIMB(true), MAX_CHILD_BEND(25.0f), MIN_CHILD_BEND(5.0f), SWAY_AMOUNT(1.0f)
{
	init();
	rotationMatrix.makeRotationMatrix(BASE_ANGLE, 0,0,1);
	clockwise = ((BASE_ANGLE < 0) ? true : false);
}

EverBranch::EverBranch(DisplayManager* manager):
	parent(NULL), MAX_CHILDREN(5),
	GROWTH_RATE(0.05f),
	BIRTHRATE(0.0025f),
	MAIN_LIMB(true),
	MAX_CHILD_BEND(25.0f),
	MIN_CHILD_BEND(5.0f),
	SWAY_AMOUNT(1.0f),
	displayManager(manager)
{
	init();
	rotationMatrix.makeRotationMatrix(BASE_ANGLE, 0,0,1);
	clockwise = ((BASE_ANGLE < 0) ? true : false);
}

EverBranch::EverBranch(EverBranch* parent)
{
	init();
	this->parent = parent;
	baseMatrix.makeRotationMatrix(ofRandomf()*25, 0,0,1);
	MAIN_LIMB = false;
}

void EverBranch::init(){
	startWidth = endWidth = 2;

	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(1);
	
	direction = ofVec3f(0,1, 0);
	numChildren = 0;
	length = 0;
	time = 0;
}

void EverBranch::grow(){
	length = length + GROWTH_RATE;

	if(numChildren == 0){
		endWidth = 0;
	} else {
		endWidth = children[0]->startWidth;
	}

	startWidth += GROWTH_RATE/10;
	texture->setAmplitude(startWidth/2);
}

void EverBranch::adjustLimb(){
	float yAngle = Y_DIRECTION.angle(direction) -180;
	angle = ((X_DIRECTION.angle(direction) > 90) ? yAngle : -yAngle);

	if(!MAIN_LIMB || parent == NULL)
		return;

	float destAngle = parent->angle + ((clockwise) ? -MAX_CHILD_BEND : MAX_CHILD_BEND);

	if(clockwise && destAngle < 0){
		destAngle = 0;
	}
	else if(!clockwise && destAngle > 0){
		destAngle = 0;
	}
	float delta = destAngle - angle;

	adjustmentMatrix.makeRotationMatrix((delta/100)/MAX_CHILD_BEND, 0,0,1);
}

void EverBranch::reproduce(){
	if(ofRandomuf() < BIRTHRATE){
		newChild();
	}
}

void EverBranch::update(){
	grow();
	reproduce();
	baseMatrix = baseMatrix * adjustmentMatrix;
	//if(parent == NULL)
	swayMatrix.makeRotationMatrix(sinf(time/10.0f*GROWTH_RATE)*(SWAY_AMOUNT+3), 0,0,1);
	direction = Y_DIRECTION * (rotationMatrix * baseMatrix * swayMatrix);
	endPosition = position + direction * length;
	weight = length;
	adjustLimb();

	for(int i=0; i< numChildren; i++){
		children[i]->setPosition((endPosition - position)*children[i]->ATTACH_POINT+position);
		children[i]->setRotationMatrix(rotationMatrix * baseMatrix * swayMatrix);
		children[i]->update();
		weight += children[i]->weight;
	}

	texture->setStartEnd(position, endPosition);

	time += SWAY_AMOUNT/5 + 1;
	if(time > 99999999){time = 0;}
}

void EverBranch::draw(){
	//texture->draw(position, endPosition);
	displayManager->addtoLayer(texture, 0);

	for(int i=0; i<numChildren; i++){
		children[i]->draw();
	}
}

void EverBranch::draw(float offset){
	texture->setStartEnd(position, endPosition);
	texture->draw(offset);
	
	for(int i=0; i<numChildren; i++){
		children[i]->draw(offset);
	}
}

void EverBranch::setPosition(ofVec2f position){
	this->position = position;
}

void EverBranch::setRotationMatrix(ofMatrix4x4 rotation){
	rotationMatrix = rotation;
}

void EverBranch::setBranchAngle(float angle){
	branchBaseMatrix.makeRotationMatrix(angle, 0,0,1);
	clockwise = ((angle < 0) ? true : false);
}

void EverBranch::setSwayAmount(float sway){
	SWAY_AMOUNT = sway;

	for(int i=0; i<numChildren; i++){
		children[i]->setSwayAmount(sway * SWAY_DECAY);
	}
}

void EverBranch::newChild(){
	if(numChildren+1 > MAX_CHILDREN)
		return;

	EverBranch* temp = new EverBranch(this);
	temp->GROWTH_RATE = GROWTH_RATE*GROWTH_DECAY;
	temp->MAX_CHILDREN = MAX_CHILDREN * CHILD_DECAY;
	temp->BIRTHRATE = BIRTHRATE * BIRTHRATE_DECAY;
	temp->MAX_CHILD_BEND = MAX_CHILD_BEND * MAX_BEND_DECAY;
	temp->MIN_CHILD_BEND = MIN_CHILD_BEND * MIN_BEND_DECAY;
	temp->SWAY_AMOUNT = SWAY_AMOUNT * SWAY_DECAY;
	temp->clockwise = clockwise;
	temp->displayManager = displayManager;
	if(numChildren == 0){
		temp->ATTACH_POINT = 1;
		temp->MAIN_LIMB = true;
	}
	else{
		temp->ATTACH_POINT = (float)(ofRandom(BRANCH_SEPERATION-1)+1)/BRANCH_SEPERATION;
	}

	children.push_back(temp);

	numChildren++;
}

void EverBranch::adjustGrowthRate(float adjust){
	GROWTH_RATE += adjust;

	for(int i=0; i<numChildren; i++){
		children[i]->adjustGrowthRate(adjust * GROWTH_DECAY);
	}
}