#include "EverTree.h"

const ofVec3f EverTree::X_DIRECTION(1,0,0);
const ofVec3f EverTree::Y_DIRECTION(0,1,0);
const float EverTree::MAX_CHILDREN = 9;
const float EverTree::BRANCH_SEPERATION = 0.30;
const string EverTree::TEXTURE_SRC = "bark.bmp";

EverTree::EverTree(DisplayManager* manager):GROWTH_RATE(0.1),length(0),swayAmount(0),numChildren(0), time(0)
{
	displayManager = manager;
	attachPointProgress = 1;
	attachPointSide = true;
	birthRate = 0.0025f;
	startWidth = 2.0f;
	endWidth = 0.0f;
	position = ofVec3f(0.0f, 0.0f);
	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(20);
	texture->setAmplitude(2);
	position = ofVec3f(200, 400, 0);
}

void EverTree::reproduce(){
	if(ofRandomuf() < birthRate){
		newChild();
	}
}

void EverTree::grow(){
	length += GROWTH_RATE;

	if(numChildren == 0){
		endWidth = 0;
	} else {
		endWidth = branch[0]->startWidth;
	}

	startWidth += GROWTH_RATE/10;
	texture->setAmplitude(startWidth/2);
}

void EverTree::sway(){
	swayMatrix.makeRotationMatrix(sinf(time/10.0f*GROWTH_RATE)*(swayAmount+length/500), 0,0,1);
	swayMatrix.rotate(180, 0,0,1);
}

void EverTree::setSway(float sway){
	swayAmount = sway;
	for(int i=0; i<numChildren; i++){
		branch[i]->setSwayAmount(sway);
	}
}

void EverTree::setDirection(){
	direction = Y_DIRECTION * (swayMatrix);
	direction.normalize();//.rotate(180, ofVec3f(0,0,1));
	endPosition = position + direction * length;
}

void EverTree::setPosition(ofVec2f position){
	this->position = position;
}

void EverTree::update(){
	reproduce();
	grow();
	sway();
	setDirection();

	for(int i=0; i<numChildren; i++){
		branch[i]->setPosition((endPosition - position)*branch[i]->ATTACH_POINT+position);
		branch[i]->setRotationMatrix(swayMatrix * branch[i]->branchBaseMatrix);
		branch[i]->update();
	}
	texture->setStartEnd(position, endPosition);

	time += swayAmount/10 + 0.25;
	if(time > 99999999){time = 0;}
}

void EverTree::draw(){
	//ofLine(position, endPosition);

	for(int i=0; i<numChildren; i++){
		branch[i]->draw();
	}
	//texture->draw(position, endPosition);
	displayManager->addtoLayer(texture, 0);
}

void EverTree::newChild(){
	if(numChildren+1 > MAX_CHILDREN)
		return;

	EverBranch* temp = new EverBranch(displayManager);
	/*temp->GROWTH_RATE = GROWTH_RATE*GROWTH_DECAY;
	temp->MAX_CHILDREN = MAX_CHILDREN * CHILD_DECAY;
	temp->BIRTHRATE = BIRTHRATE * BIRTHRATE_DECAY;
	temp->MAX_CHILD_BEND = MAX_CHILD_BEND * MAX_BEND_DECAY;
	temp->MIN_CHILD_BEND = MIN_CHILD_BEND * MIN_BEND_DECAY;
	temp->SWAY_AMOUNT = SWAY_AMOUNT * SWAY_DECAY;
	temp->clockwise = clockwise;*/
	if(numChildren == 0){
		temp->ATTACH_POINT = 1;
		temp->MAIN_LIMB = true;
	}
	else{
		temp->ATTACH_POINT = attachPointProgress;
		float tempRotation = ofRandomf() * 10 + 70 * ((attachPointSide)? 1 : -1);
		temp->setBranchAngle(tempRotation);
		attachPointSide = !attachPointSide;
		attachPointProgress -= ((attachPointSide)?BRANCH_SEPERATION:0);
	}

	branch[numChildren] = temp;

	numChildren++;
}

void EverTree::adjustGrowthRate(float adjust){
	GROWTH_RATE += adjust;

	for(int i=0; i<numChildren; i++){
		branch[i]->adjustGrowthRate(adjust);
	}
}