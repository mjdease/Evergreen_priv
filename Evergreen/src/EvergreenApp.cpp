#include "EvergreenApp.h"

enum LayerTypes {FOREGROUND, MIDGROUND, BACKGROUND};
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

long EverTime=0;

//--------------------------------------------------------------
void EvergreenApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	ofEnableAlphaBlending();
	//ofSetWindowPosition(-1390,215);
	ofEnableSmoothing();

	physicalController = new PhysicalController();
	//  \\\\.\\ must preceed the device string reported by the arduino IDE
	physicalController->init("\\\\.\\COM4", "\\\\.\\COM6", "\\\\.\\COM8");

	initUI();
	
	paused = false;

	tree = new EverTree();//Foreground);
	tree->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT*2 - 200);

	ground = new EverGround(SCREEN_HEIGHT*2, SCREEN_WIDTH, &paused);
	ground->setTree(tree);
	ground->setControllerPointer(physicalController->getLeftWind(),
									physicalController->getRightWind(),
									physicalController->getSunniness(),
									physicalController->getShakiness(),
									physicalController->getPlantType());
	ground->setUIBars(sunStat, waterStat, nutrientStat, tempStat);
}

void EvergreenApp::initUI(){

	int positionY = SCREEN_HEIGHT - 50;
	int positionX = 56;
	sunStat = new EverStats("ui/sun.png", 0.5, ofColor(247, 244, 153), ofPoint(positionX, positionY));
	waterStat = new EverStats("ui/water.png", 0.5, ofColor(91, 188, 227), ofPoint(positionX + 316,positionY));
	nutrientStat = new EverStats("ui/nutrients.png", 0.5, ofColor(91, 227, 93), ofPoint(positionX + 632, positionY));
	tempStat = new EverStats("ui/temperature.png", 0.5, ofColor(255, 115, 115), ofPoint(positionX + 948, positionY));

	pauseMenu = new PauseMenu();
	pauseMenu->setBars(sunStat, waterStat, nutrientStat, tempStat);

	displayManager = new DisplayManager(SCREEN_WIDTH, SCREEN_HEIGHT*2, SCREEN_HEIGHT);
	displayManager->setPausePointer(pauseMenu->getPositionPointer());

	UILayer = displayManager->newUILayer();
	Foreground = displayManager->newLayer();
	Midground = displayManager->newLayer();
	Background = displayManager->newLayer();
}

void EvergreenApp::togglePause(){
	paused = !paused;

	if(paused == true){
		pauseMenu->show();
	}
	else{
		pauseMenu->hide();
	}
}

//--------------------------------------------------------------
void EvergreenApp::update(){
	physicalController->updateArduino();

	//printf("fps: %f\n", ofGetFrameRate());
	//printf("num children: %d\n", tree->getNumBranches());
	//printf("depth: %d\n", tree->getDepth());

	if(paused == true){
		if(physicalController->getButtonPress()){
			if(pauseMenu->pressButton()){ // Returns false if continue, true if restart
				tree = new EverTree(); // RESTART THE TREE
			}
			togglePause();
		}
		if(physicalController->getScroll() != 0){
			pauseMenu->scroll();
		}
	}
	else{
		displayManager->setOffsetClick(physicalController->getScroll());

		ground->update();
		tree->update();

		if(physicalController->getButtonPress()){
			togglePause();
		}
	}

}

//--------------------------------------------------------------
void EvergreenApp::draw(){
	
	Background->begin();
		ground->drawBackground();
	Background->end();

	// MIDGROUND LAYER
	Midground->begin();
		ground->drawMidground();
	Midground->end();

	// FOREGROUND LAYER
	Foreground->begin();
		ground->draw();
	Foreground->end();

	// UI LAYER
	UILayer->begin();
		pauseMenu->draw();

		if(paused == false){
			sunStat->draw();
			waterStat->draw();
			nutrientStat->draw();
			tempStat->draw();
		}
	UILayer->end();

	displayManager->draw();
}

//--------------------------------------------------------------
void EvergreenApp::keyPressed(int key){
	switch(key){
		/*
		case 32: // Space
			togglePause();
			break;
			*/
		case 357: // Up
			tree->TREE_HEALTH += 0.1f;
			break;
		case 359: // Down
			tree->TREE_HEALTH -= 0.1f;
			break;

		case 356: // Left
			tree->swayAmount -= 0.1f;
			break;
		case 358: // Right
			tree->swayAmount += 0.1f;
			break;

		case 360: // page up
			displayManager->setOffsetClick(1);
			break;
		case 361: // page down
			displayManager->setOffsetClick(-1);
			break;
	}
	
	printf("Key: %d\n", key);
	printf("sway: %f\n", tree->swayAmount);
	printf("Health: %f\n", tree->TREE_HEALTH);
	printf("fps: %f\n", ofGetFrameRate());
	printf("frame: %d\n", EverTime);
	printf("\n");

	//up arrow = scroll wheel away from user
	//down arrow = scroll wheel towards user
	//enter = button press (don't hold the key)
	//right arrow = adds easterly wind (from the left windmill)
	//left arrow = adds westerly wind (from the right windmill)
	//F1 = increases sunniness
	//F2 = increases shakiness
	//F3 = changes through plant type
	physicalController->debugKeyPress(key);
}

//--------------------------------------------------------------
void EvergreenApp::keyReleased(int key){
	physicalController->debugKeyReleased(key);
}

//--------------------------------------------------------------
void EvergreenApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void EvergreenApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void EvergreenApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void EvergreenApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void EvergreenApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void EvergreenApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void EvergreenApp::dragEvent(ofDragInfo dragInfo){ 

}