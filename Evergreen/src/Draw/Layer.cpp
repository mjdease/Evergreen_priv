#include "Layer.h"


Layer::Layer(void) {
	index = 0;
	offset = 0;
}

void Layer::addtoDraw(EverTexture* addedTexture) {
	texture[index] = addedTexture;
	index++;
}

void Layer::draw() {
	for(int i = 0; i < index; i++) {
		texture[i]->draw(offset);
	}

	index = 0;
}

void Layer::setOffset(float offset) {
	this->offset = offset;
}

Layer::~Layer(void) {
}