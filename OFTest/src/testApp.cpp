#include "testApp.h"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define MAX_PARTICLES 2000

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
	ofEnableSmoothing();
	ofNoFill();
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetFrameRate(60);

	//particles = new Particle*[MAX_PARTICLES];

	for( int i=0; i<MAX_PARTICLES; i++){
		//particles[i] = new Particle(WINDOW_WIDTH, WINDOW_HEIGHT);
		particleVector.push_back(Particle(WINDOW_WIDTH, WINDOW_HEIGHT));
	}
}

//--------------------------------------------------------------
void testApp::update(){
	for( int i=0; i<MAX_PARTICLES; i++){
		//particles[i]->update();
		particleVector[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	for( int i=0; i<MAX_PARTICLES; i++){
		//particles[i]->draw();
		particleVector[i].draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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