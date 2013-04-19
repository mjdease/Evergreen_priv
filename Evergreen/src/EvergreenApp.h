#pragma once

#include "ofMain.h"
#include "Tree/EverTree.h"
#include "Environment/EverGround.h"
#include "Environment/EverCloud.h"
#include "DisplayManager.h"
#include "PhysicalController/PhysicalController.h"
#include "Draw/SimpleTexture.h"
#include "Draw\PauseMenu.h"
#include "Audio.h"
#include <ctime>

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

	private:
		bool paused;

		Audio* musicSound;
		Audio* ambientSound;

		EverStats* sunStat;
		EverStats* waterStat;
		EverStats* nutrientStat;
		EverStats* tempStat;

		PhysicalController* physicalController;

		PauseMenu* pauseMenu;
		DisplayManager* displayManager;
		DisplayLayer* UILayer;
		DisplayLayer* Foreground;
		DisplayLayer* Midground;
		DisplayLayer* Background;

		EverTree* tree;

		EverGround* ground;

		float* shakeAmount;

		void initUI();
		void togglePause();

		clock_t startTime;
};
