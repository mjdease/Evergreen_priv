#include "testApp.h"

enum LayerTypes {FOREGROUND, MIDGROUND, BACKGROUND};

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	wind = 0;
	//physicalController = new PhysicalController();
	//physicalController->init("COM4");

	displayManager = new DisplayManager();
	displayManager->newLayer();
	displayManager->newLayer();
	displayManager->newLayer();

	tree = new EverTree(displayManager);
	tree->setPosition(ofVec2f(640.0f, 580.0f));

	ground = new EverGround(displayManager);

	midground = new SimpleTexture("environment/midground.png");
	midground->setPosition(0,0);

	background = new SimpleTexture("environment/background/mountains.png");
	background->setPosition(0,0);

	sky = new SimpleTexture("environment/sky.png");
	sky->setPosition(0,-2200);

	for(int i=0; i<10; i++){
		clouds[i] = new EverCloud();
	}

	//physicalController = new PhysicalController();
}

//--------------------------------------------------------------
void testApp::update(){
	//physicalController->updateArduino();

	//wind = (physicalController->getLeftWind() + physicalController->getRightWind()) * 15;
	tree->setSway(wind);

	//displayManager->setOffsetClick(physicalController->getScroll());

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
	
	if(key == 32){
		wind += 1;
	}

	if(key == 357){
		displayManager->setOffsetClick(1);
	}
	else if(key == 359){
		displayManager->setOffsetClick(-1);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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