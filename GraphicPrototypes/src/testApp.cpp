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
	displayMan->newLayer();
	time = 0;
	ground = new EverGround();

	//displayMan->addtoLayer(testTx, 2);
	//ofLoadImage(testTex,"texture.bmp");
}

//--------------------------------------------------------------
void testApp::update(){

	//rotation++;
	//cout << ofGetFrameRate() << "\n";

	p1 = ofPoint(100,600/2);
	p2 = ofPoint(mouseX, mouseY);
	branchTx->setStartEnd(p1, p2);
	ground->health = (float)mouseX / 1280.0;

	displayMan->layers[0]->setOffset(sinf(time)*20);

	time+=0.1;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//displayManager->drawLayers();
	//branchTx->draw(p1, p2);
	//branchTx->draw(p1, p2);

	displayMan->addtoLayer(branchTx, 0);
	displayMan->draw();

	ground->draw();
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
