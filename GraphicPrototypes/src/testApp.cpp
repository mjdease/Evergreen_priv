#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowShape(1280, 800);
	rotation = 0;
	startWidth = 50;
	endWidth = 0;
	branchTx = new BranchTexture(&startWidth, &endWidth);
	branchTx->loadTexture("bark.bmp");
	
	displayMan = new DisplayManager();
	//displayMan->addtoLayer(testTx, 2);

	//ofLoadImage(testTex,"texture.bmp");
}

//--------------------------------------------------------------
void testApp::update(){

	//rotation++;

	//cout << ofGetFrameRate() << "\n";

	p1 = ofPoint(100,600/2);
	p2 = ofPoint(mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//displayManager->drawLayers();
	//branchTx->draw(p1, p2);
	branchTx->draw(p1, p2);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	branchTx->setResolution(branchTx->resolution + 1);
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
