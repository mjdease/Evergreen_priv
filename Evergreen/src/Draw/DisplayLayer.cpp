#include "DisplayLayer.h"


DisplayLayer::DisplayLayer(int width, int height, int totalHeight, float* scale) {
	index = 0;
	offset = 0;
	buffer.allocate(width, height, GL_RGBA, 0);
	this->width = width;
	this->height = height;
	screenOffset = totalHeight - height;
	this->scale = scale;
	multiplier = 1;
	add = 0;
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

	if(scale == NULL){
		buffer.draw(0,offset+screenOffset,width, height);
	}
	else{
		if(*scale < 1){
			multiplier -= multiplier / 5;
			add = -300;
		}
		else{
			multiplier += (1 - multiplier) / 5;
			add = 0;
		}
		buffer.draw(width - (*scale *width),(multiplier) * (offset+screenOffset) + add,*scale * width, *scale * height);
	}
	index = 0;
}

void DisplayLayer::setOffset(float offset) {
	this->offset = offset;
}

DisplayLayer::~DisplayLayer(void) {
}