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
}


PauseMenu::~PauseMenu(void)
{
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
	
	fontBody.drawString("time elapsed:\ntree height:\ntree health:\nleaf count:\nbranch count:", posTreeStats.x + menuX, posTreeStats.y);
	char fpsStr[255];
	
	sprintf(fpsStr, "%i\n%i\n%i\n%i\n%i", 1,2,3,4,5); // stats here

	fontBody.drawString(fpsStr, posTreeStats.x + menuX + 200, posTreeStats.y);

	// stat bars
	eStatsSun->draw();
	eStatsWater->draw();
	eStatsNutrients->draw();
	eStatsTemperature->draw();

	// pause and restart buttons
	sprintf(pause,"pause");
	fontBody.drawString(pause,menuX + 50, 700);

	sprintf(restart,"restart");
	fontBody.drawString(restart,menuX + 50, 750);
}