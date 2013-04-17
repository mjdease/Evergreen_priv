#pragma once
#include "ofMain.h"
#include "Draw/DisplayLayer.h"

class DisplayManager
{
public:
	int offsetClick;
	int width, height;
	float clickAmount;
	float offset;
	float parallax;
	vector<DisplayLayer*> layers;
	DisplayLayer* interfaceLayer;

	void setPausePointer(float* pausePointer);
	
	DisplayLayer* newLayer();
	DisplayLayer* newUILayer();
	//void addtoLayer(EverTexture* tx, int layerNumber);
	//void addtoLayer(EverTexture* tx, DisplayLayer* layer);
	void drawLayer(int layerIndex);
	void draw();
	
	void setOffset(float offset);
	void setOffsetClick(int offset);

	DisplayManager(int width, int height, int ScreenHeight);
	~DisplayManager(void);

private:
	int destOffset;
	int screenHeight;
	float* pausePosition;

	float scale;
};