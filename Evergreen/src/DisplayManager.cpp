#include "DisplayManager.h"

DisplayManager::DisplayManager(int width, int height, int ScreenHeight):parallax(0.5)
{
	offsetClick = 0;
	clickAmount = 50;
	this->width = width;
	this->height = height;
	screenHeight = ScreenHeight;
	destOffset = offset = 0;
}
/*
void DisplayManager::addtoLayer(EverTexture* tx, int layerNumber) {
	layers[layerNumber]->addtoDraw(tx);
}

void DisplayManager::addtoLayer(EverTexture* tx, DisplayLayer* layer) {
	layer->addtoDraw(tx);
}
*/
DisplayLayer* DisplayManager::newLayer() {
	DisplayLayer* temp = new DisplayLayer(width, height, screenHeight);
	layers.push_back(temp);
	return temp;
}

void DisplayManager::drawLayer(int layerIndex) {
	// draw a layer
	layers[layerIndex]->draw();
}

void DisplayManager::draw() {
	ofEnableAlphaBlending();

	offset = (destOffset - offset) / 10 + offset;
	for(int i = layers.size()-1; i >= 0; i--) {
		layers[i]->setOffset(offset / (parallax * i + 1));
		drawLayer(i);
	}

	ofDisableAlphaBlending();  
}

void DisplayManager::setOffsetClick(int click){
	this->offsetClick += click;
	offsetClick = ((offsetClick < 0)?0:offsetClick);
	setOffset(this->offsetClick * clickAmount);
}

void DisplayManager::setOffset(float destOffset){
	this->destOffset = destOffset;
}

DisplayManager::~DisplayManager(void)
{

}