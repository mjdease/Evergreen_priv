#include "DisplayLayer.h"


DisplayLayer::DisplayLayer(int width, int height, int totalHeight) {
	index = 0;
	offset = 0;
	buffer.allocate(width, height, GL_RGBA, 0);
	this->width = width;
	this->height = height;
	screenOffset = totalHeight - height;
}

/*
void DisplayLayer::addtoDraw(EverTexture* addedTexture) {
	texture[index] = addedTexture;
	index++;
}
*/

void DisplayLayer::begin(){
	buffer.begin();
	ofClear(0, 0, 0, 0);
}

void DisplayLayer::end(){
	buffer.end();
}

void DisplayLayer::draw() {
	buffer.draw(0,offset+screenOffset,width, height);
	index = 0;
}

void DisplayLayer::setOffset(float offset) {
	this->offset = offset;
}

DisplayLayer::~DisplayLayer(void) {
}