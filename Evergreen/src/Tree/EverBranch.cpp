#include "EverBranch.h"

#define minStuntLength 20

const float EverBranch::BIRTH_DECAY = 0.6f;
const float EverBranch::CHILD_DECAY = 0.6f;
const float EverBranch::WIDTH_DECAY = 0.6f;
const int EverBranch::MAX_DEPTH = 10;

const string EverBranch::TEXTURE_SRC = "bark.bmp";

int* EverBranch::GlobalDepth = NULL;
int* EverBranch::GlobalLimbDepth = NULL;
float* EverBranch::TreeHealth = NULL;
float* EverBranch::swayAmount = NULL;
int* EverBranch::rootSiblingNum = NULL;
vector <EverBranch*>* EverBranch::siblings = NULL;

float* EverBranch::sun = NULL;
float* EverBranch::water = NULL;
float* EverBranch::nutrient = NULL;
float* EverBranch::temperature = NULL;
int* EverBranch::numBranches = NULL;

void EverBranch::updateAngle(){
	// Adjust sun/ground angle
	float sunAngle = -globalAngle;
	float groundAngle = ((globalAngle < 0) ? -180 : 180) - globalAngle;

	baseAngle += (*TreeHealth/100.0f) * sunAngle/(350.0f * depth);
	if(parent != NULL)
		baseAngle += (1 - *TreeHealth/100.0f) * groundAngle/(500.0f * depth);

	// Affected by siblings
	int siblingNum = (parent == NULL) ? *rootSiblingNum : parent->numChildren;
	for(int i=0; i<siblingNum; i++){
		EverBranch* sibling = (parent == NULL) ? (*siblings)[i] : parent->children[i];
		if(sibling == this){
			continue;
		}

		float attachDiff = abs(attachPoint - sibling->attachPoint);
		float angleDiff = baseAngle - sibling->baseAngle;
		
		baseAngle += ((1 - attachDiff)/30 + length/500) * 5 / angleDiff;
	}

	// Adjust for max/min angles
	if(angleMultiplier * baseAngle < angleMultiplier * minAngle && parent != NULL){
		baseAngle += (minAngle - baseAngle)/ 500.0f;
	}
	else if(angleMultiplier * baseAngle > angleMultiplier * maxAngle){
		baseAngle += (maxAngle - baseAngle)/ 500.0f;
	}

	sway();

	angle = baseAngle + swayAngle;
}

void EverBranch::sway(){
	swayAngle = (sinf(ofGetFrameNum() * (*swayAmount) / 300.0f) * (*swayAmount) + *swayAmount) * (limbDepth/2 + 1);
	//swayAngle *= 0.9f;
	//swayAngle += (sinf(ofGetFrameNum()/(*swayAmount * 200.0f)) * (*swayAmount*depth/2))/500.0f;
	//swayAngle += (sinf(ofGetFrameNum() * (*swayAmount) / 300.0f) * (*swayAmount*2.0f) / 10.0f + (*swayAmount*2.0f) / 10.0f)/(depth*1.5);
}

void EverBranch::grow(){
	float healthMult = (*TreeHealth-50.0f)/100.0f;
	float growthTarget;
	growthTarget = (healthMult * (350.0f/depth - length)) / 3000.0f;

	if(healthMult > 0)
		length += growthTarget;
	else if(healthMult < 0 && length < minStuntLength/(limbDepth/5 + 1)){
	}
	else if(healthMult < 0){
		length = ofClamp(length + growthTarget, minStuntLength/(limbDepth/5 + 1), length);
	}

	if(mainBranch == false){
		startWidth = parent->endWidth/(limbDepth/2 + 1);
	}
	else if(parent != NULL){
		startWidth = parent->endWidth;
	}
	else if(baseStartWidth != NULL){
		startWidth = *baseStartWidth;
	}

	if(numChildren == 0){
		endWidth = 1;
	}
	else{
		endWidth = startWidth/2 + 1;
	}
}

void EverBranch::reproduce(){
	if(numChildren < maxChildren && ofRandomuf() < birthRate && depth < MAX_DEPTH){
		newChild();
	}
}

void EverBranch::update(){
	if(parent == NULL){ globalAngle = convertAngle(angle); }
	else{ globalAngle = convertAngle(angle + parent->globalAngle); }
	updateAngle();

	grow();
	reproduce();

	for(int i=0; i<numChildren; i++){
		children[i]->update();
	}

	texture->setStartEnd(ofPoint(0,0), ofPoint(0, length));

	leaf->setPosition(length);

	if(startWidth > 1 && endWidth >= 0)
		leaf->update();
}

void EverBranch::draw(){
	ofRotate(angle);

	texture->draw(0);
	/*ofSetColor(0, 255, 0);
	if(depth < MAX_DEPTH+1){
		ofSetColor(255, 0, 0);
	}
	ofLine(0,0,0,length);
	//ofCircle(0,0,2);
	ofSetColor(0, 255, 0);*/
	

	//layer->addtoDraw(texture);
	//texture->draw(0);

	for(int i=0; i<numChildren; i++){
		ofPushMatrix();
		ofTranslate(0,length*children[i]->attachPoint, 0);
		children[i]->draw();
		ofPopMatrix();
	}
	leaf->draw();
}

void EverBranch::newChild(){
	*numBranches++;
	EverBranch* temp = new EverBranch(this);
	children.push_back(temp);
	numChildren++;
}

EverBranch::EverBranch(){
	startWidth = 10;
	endWidth = 1;
	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(1);

	depth = 1;
	parent = NULL;
	birthRate = 0.003;
	limbDepth = 1;

	baseAngle = ofRandomf()*60;
	swayAngle = 0;
	angle = baseAngle + swayAngle;//ofRandom(60);
	globalAngle = convertAngle(angle);
	angleMultiplier = (globalAngle < 0) ? -1 : 1;
	minAngle = angleMultiplier * ofRandom(10, 10 + 20/depth);
	maxAngle = angleMultiplier * ofRandom(30, 45 + 30/depth);
	attachPoint = 1;

	length = 0;
	depth = 1;
	numChildren = 0;
	maxChildren = 5;
	mainBranch = true;

	baseStartWidth = NULL;
	
	int leafType = 2;

	if(*water < 0.1){
		leafType = rand() %2 + 3;
	}
	else if(*nutrient < 0.3){
		leafType = 6;
	}
	else if(*temperature < 0.2){
		leafType = 5;
	}
	else{
		leafType = rand() % 2 + 1;
	}

	leaf = new EverLeaf(leafType);
}

EverBranch::EverBranch(EverBranch* parent){

	this->parent = parent;
	depth = parent->depth + 1;
	if(depth > *GlobalDepth){ *GlobalDepth = depth; }

	if(parent->numChildren >= 1){
		limbDepth = parent->limbDepth + 1;
		if(*GlobalLimbDepth < limbDepth) { *GlobalLimbDepth = limbDepth; }
		birthRate = parent->birthRate * BIRTH_DECAY;
		mainBranch = false;
	}
	else{
		birthRate = parent->birthRate;
		limbDepth = parent->limbDepth;
		mainBranch = true;
	}

	texture = new BranchTexture(&startWidth, &endWidth);
	texture->loadTexture(TEXTURE_SRC);
	texture->setResolution(1);

	baseAngle = ofRandomf()*60;
	swayAngle = 0;
	angle = baseAngle + swayAngle;//ofRandom(60);
	globalAngle = convertAngle(angle + parent->globalAngle);
	angleMultiplier = (globalAngle < 0) ? -1 : 1;
	minAngle = angleMultiplier * ofRandom(10, 10 + 20/depth);
	maxAngle = angleMultiplier * ofRandom(30, 45 + 30/depth);

	length = 0;
	attachPoint = (parent->numChildren < 1) ? 1 : ofRandomuf();
	numChildren = 0;
	maxChildren = parent->maxChildren * CHILD_DECAY;

	baseStartWidth = NULL;
	
	int leafType = 2;

	if(*water < 0.1){
		leafType = rand() %2 + 3;
	}
	else if(*nutrient < 0.3){
		leafType = 6;
	}
	else if(*temperature < 0.2){
		leafType = 5;
	}
	else{
		leafType = rand() % 2 + 1;
	}

	leaf = new EverLeaf(leafType);
}

void EverBranch::setPointers(float* TreeHealth, int* depth, int* limbDepth, int* rootSiblings, vector <EverBranch*>* siblingBranches, float* swayAmount, int* numBranches){
	EverBranch::TreeHealth = TreeHealth;
	EverBranch::GlobalDepth = depth;
	EverBranch::rootSiblingNum = rootSiblings;
	EverBranch::siblings = siblingBranches;
	EverBranch::GlobalLimbDepth = limbDepth;
	EverBranch::swayAmount = swayAmount;
	EverBranch::numBranches = numBranches;
}

EverBranch::~EverBranch(void)
{
}

float EverBranch::convertAngle(float angle){
	angle = fmodf(angle, 360.0f);
	return ((angle<=180.0f) ? angle : angle-360);
}

void EverBranch::setStartWidth(float* start){
	baseStartWidth = start;
}

void EverBranch::setEnvPointers(float* sun, float* water, float* nutrient, float* temperature){
	EverBranch::sun = sun;
	EverBranch::water = water;
	EverBranch::nutrient = nutrient;
	EverBranch::temperature = temperature;
}
