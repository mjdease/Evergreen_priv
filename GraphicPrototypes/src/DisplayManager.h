#pragma once
#include "ofMain.h"
#include "Layer.h"

class DisplayManager
{
public:
	/*ofImage foreground;
	ofImage midground;
	ofImage background;
	ofImage foreground_a;
	ofImage midground_a;*/

	ofTexture mix[3];

	// 0 = back, 1 = mid, 2 = foreground

	//Layer layer[3];
	vector<Layer*> layers;

	DisplayManager(void);
	~DisplayManager(void);

	int newLayer();
	void addtoLayer(EverTexture* tx, int layerNumber);
	void drawLayer(int layerIndex);
	void draw();

	/*void drawLayers();
	ofTexture getMask(ofImage img, ofImage img_a);*/

};