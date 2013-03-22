#pragma once
#include "ofMain.h"
#include "Draw/Layer.h"

class DisplayManager
{
public:
	/*ofImage foreground;
	ofImage midground;
	ofImage background;
	ofImage foreground_a;
	ofImage midground_a;*/

	//ofTexture mix[3];
	int offsetClick;
	float clickAmount;
	float offset;
	float parallax;

	// 0 = back, 1 = mid, 2 = foreground

	//Layer layer[3];
	vector<Layer*> layers;

	DisplayManager(void);
	~DisplayManager(void);

	int newLayer();
	void addtoLayer(EverTexture* tx, int layerNumber);
	void drawLayer(int layerIndex);
	void draw();
	
	void setOffset(float offset);
	void setOffsetClick(int offset);

	/*void drawLayers();
	ofTexture getMask(ofImage img, ofImage img_a);*/

};