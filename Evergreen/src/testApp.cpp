#include "testApp.h"

enum LayerTypes {FOREGROUND, MIDGROUND, BACKGROUND};

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	wind = 0;
	physicalController = new PhysicalController();
	//  \\\\.\\ must preceed the device string reported by the arduino IDE
	physicalController->init("\\\\.\\COM4", "\\\\.\\COM6", "\\\\.\\COM8");

	displayManager = new DisplayManager();
	displayManager->newLayer();
	displayManager->newLayer();
	displayManager->newLayer();

	tree = new EverTree(displayManager);
	tree->setPosition(ofVec2f(640.0f, 580.0f));

	ground = new EverGround(displayManager);
	ground->setTree(tree);

	midground = new SimpleTexture("environment/midground.png");
	midground->setPosition(0,0);

	background = new SimpleTexture("environment/background/mountains.png");
	background->setPosition(0,0);

	sky = new SimpleTexture("environment/sky.png");
	sky->setPosition(0,-2200);

	for(int i=0; i<10; i++){
		clouds[i] = new EverCloud();
	}
}

//--------------------------------------------------------------
void testApp::update(){
	physicalController->updateArduino();

	wind = (physicalController->getLeftWind() + physicalController->getRightWind()) * 15;

	tree->setSway(wind);

	displayManager->setOffsetClick(physicalController->getScroll());

	tree->update();

	if(wind > 5){
		ground->health += 0.05;
	}
	ground->health-=0.001;
}

//--------------------------------------------------------------
void testApp::draw(){
	ground->draw();
	tree->draw();
	
	displayManager->addtoLayer(midground, MIDGROUND);
	
	for(int i=0; i<10; i++){
		displayManager->addtoLayer(clouds[i], MIDGROUND);
	}

	displayManager->addtoLayer(sky, BACKGROUND);
	displayManager->addtoLayer(background, BACKGROUND);

	displayManager->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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
void testApp::keyReleased(int key){
	physicalController->debugKeyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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