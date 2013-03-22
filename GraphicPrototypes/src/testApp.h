#pragma once

#include "ofMain.h"
#include "EverTexture.h"
#include "BranchTexture.h"
#include "DisplayManager.h"
#include "Layer.h"
#include "EverGround.h"
#include "EverFlower.h"
#include "EverCloud.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		ofTexture testTx;

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float startWidth, endWidth;
		
		// EverTexture* texture;
		BranchTexture* branchTx;
		float rotation;

		// Display manager
		DisplayManager* displayMan;

		ofPoint p1;
		ofPoint p2;

		EverGround* ground;
		EverFlower* flower;
		EverCloud* cloud;

		float time;
};
