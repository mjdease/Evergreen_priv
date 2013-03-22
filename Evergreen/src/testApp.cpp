#include "testApp.h"

enum LayerTypes {FOREGROUND, MIDGROUND, BACKGROUND};

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	wind = 0;
	
	displayManager = new DisplayManager();
	displayManager->newLayer();
	displayManager->newLayer();
	displayManager->newLayer();

	tree = new EverTree(displayManager);
	//physicalController = new PhysicalController();
}

//--------------------------------------------------------------
void testApp::update(){
	//physicalController->updateArduino();

	//wind = (physicalController->getLeftWind() + physicalController->getRightWind()) * 15;
	tree->setSway(wind);

	//displayManager->setOffsetClick(physicalController->getScroll());

	tree->update();
	printf("%f\n", ofGetFrameRate());
}

//--------------------------------------------------------------
void testApp::draw(){
	tree->draw();
	displayManager->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	wind += 1;
	tree->setSway(wind);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	tree->setPosition(ofVec2f((float)x, (float)y));
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}