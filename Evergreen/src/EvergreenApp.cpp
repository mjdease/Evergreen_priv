#include "EvergreenApp.h"

enum LayerTypes {FOREGROUND, MIDGROUND, BACKGROUND};
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

//--------------------------------------------------------------
void EvergreenApp::setup(){
	//ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	ofEnableAlphaBlending();
	//ofSetWindowPosition(-1390,215);
	ofEnableSmoothing();
	ofNoFill();
	//physicalController = new PhysicalController();
	//physicalController->init("COM4");

	displayManager = new DisplayManager(SCREEN_WIDTH, SCREEN_HEIGHT*2, SCREEN_HEIGHT);
	Foreground = displayManager->newLayer();
	Midground = displayManager->newLayer();
	Background = displayManager->newLayer();

	//branch = new EverBranch(Foreground);
	tree = new EverTree(Foreground);//Foreground);
	tree->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT*2 - 100);
}

//--------------------------------------------------------------
void EvergreenApp::update(){
	//printf("fps: %f\n", ofGetFrameRate());
	//printf("num children: %d\n", tree->getNumBranches());
	//printf("depth: %d\n", tree->getDepth());
	//branch->setPosition(ofVec2f(ofGetMouseX(), ofGetMouseY()));

	//branch->update();
	tree->update();
}

//--------------------------------------------------------------
void EvergreenApp::draw(){
	Foreground->begin();
	tree->draw();
	Foreground->end();

	displayManager->draw();
}

//--------------------------------------------------------------
void EvergreenApp::keyPressed(int key){
	switch(key){
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
	printf("\n");
}

//--------------------------------------------------------------
void EvergreenApp::keyReleased(int key){

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