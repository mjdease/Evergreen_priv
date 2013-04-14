#include "PauseMenu.h"

PauseMenu::PauseMenu(void)
{
	fontTitle.loadFont("ui/whitney-bold.ttf", 32);
	fontSubtitle.loadFont("ui/whitney-bold.ttf", 22);
	fontBody.loadFont("ui/whitney-book.ttf", 14);
	
	posTreeStatsTitle = ofVec2f(50, 120);
	posTreeStats = ofVec2f(50, 150);

	posEnvStatsTitle = ofVec2f(50, 400);
	posEnvStats = ofVec2f(50, 430);
	
	// environment statistics
	sun = 50.0;
	water = 25.0;
	nutrients = 25.0;
	temperature = 75.0;

	eStatsSun =	new EverStats("ui/sun.png", sun, ofColor(247, 244, 153), ofVec2f(posEnvStats.x, posEnvStats.y));
	eStatsWater = new EverStats("ui/water.png", water, ofColor(91, 188, 227), ofVec2f(posEnvStats.x, posEnvStats.y + 50));
	eStatsNutrients = new EverStats("ui/nutrients.png", nutrients, ofColor(91, 227, 93), ofVec2f(posEnvStats.x, posEnvStats.y + 100));
	eStatsTemperature = new EverStats("ui/temperature.png", temperature, ofColor(255, 115, 115), ofVec2f(posEnvStats.x, posEnvStats.y + 150));
}


PauseMenu::~PauseMenu(void)
{
}

void PauseMenu::draw(void) {
	// black bg
	ofSetColor(0);
	ofRect(0, 0, 400, 800);

	// stats
	ofSetColor(255);
	fontTitle.drawString("evergreen", 50, 60);
	fontSubtitle.drawString("tree stats", posTreeStatsTitle.x, posTreeStatsTitle.y);
	fontSubtitle.drawString("environment stats", posEnvStatsTitle.x, posEnvStatsTitle.y);
	
	fontBody.drawString("time elapsed:\ntree height:\ntree health:\nleaf count:\nbranch count:", posTreeStats.x, posTreeStats.y);
	char fpsStr[255];
	
	sprintf(fpsStr, "%i\n%i\n%i\n%i\n%i", 1,2,3,4,5); // stats here

	fontBody.drawString(fpsStr, posTreeStats.x + 200, posTreeStats.y);

	// stat bars
	eStatsSun->draw();
	eStatsWater->draw();
	eStatsNutrients->draw();
	eStatsTemperature->draw();

	// pause and restart buttons
	sprintf(pause,"pause");
	fontBody.drawString(pause,50,700);

	sprintf(restart,"restart");
	fontBody.drawString(restart,50,750);
}