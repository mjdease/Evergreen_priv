#pragma once

#include "ofMain.h"
#include "EverTexture.h"
#include "BranchTexture.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//EverTexture* texture;
		BranchTexture* texture;
		float rotation;

		ofPoint p1;
		ofPoint p2;
};
