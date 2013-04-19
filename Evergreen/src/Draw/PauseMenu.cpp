#include "PauseMenu.h"

PauseMenu::PauseMenu(void)
{
	width = 400;
	height = 800;

	fontTitle.loadFont("ui/whitney-bold.ttf", 32);
	fontSubtitle.loadFont("ui/whitney-bold.ttf", 22);
	fontBody.loadFont("ui/whitney-book.ttf", 14);
	
	posTreeStatsTitle = ofPoint(50, 120);
	posTreeStats = ofPoint(50, 150);

	posEnvStatsTitle = ofPoint(50, 400);
	posEnvStats = ofPoint(50, 430);

	menuX = destMenuX = -width;

	menuDrawn = false;

	highlighted = CONTINUE;
}

bool PauseMenu::pressButton(){
	if(highlighted == CONTINUE){
		return false;
	}
	else if(highlighted == RESTART){
		return true;
	}
}
void PauseMenu::scroll(){
	highlighted = (highlighted == RESTART) ? CONTINUE : RESTART;
}

float* PauseMenu:: getPositionPointer(){
	return &displayX;
}

void PauseMenu::setBars(EverStats* sun, EverStats* water, EverStats* nutrient, EverStats* temp){
	eStatsSun = sun;
	eStatsWater = water;
	eStatsNutrients = nutrient;
	eStatsTemperature = temp;
}

void PauseMenu::show(){
	destMenuX = 0;

	menuDrawn = true;
}

void PauseMenu::hide(){
	destMenuX = -width;

	menuDrawn = false;
}

void PauseMenu::toggle(){
	if(menuDrawn == false)
		show();
	else
		hide();
}

void PauseMenu::draw(void) {
	menuX += (destMenuX - menuX)/5.0f;
	displayX = width + menuX;

	if(menuX < -width + 5){
		eStatsSun->resetPosition();
		eStatsWater->resetPosition();
		eStatsNutrients->resetPosition();
		eStatsTemperature->resetPosition();
		menuX = -width;
		return;
	}
	else{
		eStatsSun->setPosition(ofPoint(posEnvStats.x + menuX, posEnvStats.y));
		eStatsWater->setPosition(ofPoint(posEnvStats.x + menuX, posEnvStats.y + 50));
		eStatsNutrients->setPosition(ofPoint(posEnvStats.x + menuX, posEnvStats.y + 100));
		eStatsTemperature->setPosition(ofPoint(posEnvStats.x + menuX, posEnvStats.y + 150));
	}


	// black bg
	ofSetColor(0);
	ofRect(menuX, 0, 400, 800);

	// stats
	ofSetColor(255);
	fontTitle.drawString("evergreen", 50 + menuX, 60);
	fontSubtitle.drawString("tree stats", posTreeStatsTitle.x + menuX, posTreeStatsTitle.y);
	fontSubtitle.drawString("environment stats", posEnvStatsTitle.x + menuX, posEnvStatsTitle.y);
	
	fontBody.drawString("time elapsed:\ntree health:\nbranch count:", posTreeStats.x + menuX, posTreeStats.y);
	char fpsStr[255];
	
	sprintf(fpsStr, "%i minutes\n%i\n%i", (int)(clock() - *startTime)/60/CLOCKS_PER_SEC,(int)*treeHealth,*numBranches); // stats here

	fontBody.drawString(fpsStr, posTreeStats.x + menuX + 200, posTreeStats.y);

	// stat bars
	eStatsSun->draw();
	eStatsWater->draw();
	eStatsNutrients->draw();
	eStatsTemperature->draw();

	// pause and restart buttons
	int continueYPosition = 678;
	int restartYPosition = 728;

	sprintf(pause,"Continue");
	fontBody.drawString(pause,menuX + 50, 700);

	sprintf(restart,"Exit");
	fontBody.drawString(restart,menuX + 50, 750);

	ofNoFill();
	ofRect(menuX + 43, (highlighted == RESTART)?restartYPosition:continueYPosition, 100, 30);
	ofFill();
}

void PauseMenu::setStats(clock_t* time, int* branches, float* health){
	startTime = time;
	numBranches = branches;
	treeHealth = health;
}

PauseMenu::~PauseMenu(void)
{
}