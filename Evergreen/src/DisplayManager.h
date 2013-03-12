#include "ofMain.h"
#pragma once

class DisplayManager
{
public:
	DisplayManager(void);
	~DisplayManager(void);

	bool drawTo(string layer, ofTexture texture, ofVec2f location);
};

