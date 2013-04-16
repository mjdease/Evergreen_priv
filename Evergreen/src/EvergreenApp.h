#pragma once

#include "ofMain.h"
#include "Tree/EverTree.h"
#include "Environment/EverGround.h"
#include "Environment/EverCloud.h"
#include "DisplayManager.h"
#include "PhysicalController/PhysicalController.h"
#include "Draw/SimpleTexture.h"

class EvergreenApp : public ofBaseApp{

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

		DisplayManager* displayManager;
		PhysicalController* physicalController;
		
		DisplayLayer* Foreground;
		DisplayLayer* Midground;
		DisplayLayer* Background;

		EverBranch* branch;
		EverTree* tree;
};
