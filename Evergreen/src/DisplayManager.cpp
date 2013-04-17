#include "DisplayManager.h"

DisplayManager::DisplayManager(int width, int height, int ScreenHeight):parallax(0.5)
{
	offsetClick = 0;
	clickAmount = 50;
	this->width = width;
	this->height = height;
	screenHeight = ScreenHeight;
	destOffset = offset = 0;
	interfaceLayer = NULL;
}

void DisplayManager::setPausePointer(float* pausePointer){
	pausePosition = pausePointer;
}

DisplayLayer* DisplayManager::newLayer() {
	DisplayLayer* temp = new DisplayLayer(width, height, screenHeight, &scale);
	layers.push_back(temp);
	return temp;
}

DisplayLayer* DisplayManager::newUILayer() {
	DisplayLayer* temp = new DisplayLayer(width, screenHeight, screenHeight, NULL);
	temp->setOffset(0);
	interfaceLayer = temp;
	return temp;
}

void DisplayManager::drawLayer(int layerIndex) {
	// draw a layer
	layers[layerIndex]->draw();
}

void DisplayManager::draw() {
	scale = (width - *pausePosition) / width;

	ofEnableAlphaBlending();

	offset = (destOffset - offset) / 10 + offset;
	for(int i = layers.size()-1; i >= 0; i--) {
		layers[i]->setOffset(offset / (parallax * i + 1));
		drawLayer(i);
	}
	interfaceLayer->draw();

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