#include "SimpleTexture.h"

SimpleTexture::SimpleTexture(string src):EverTexture(src)
{
	loadTexture(src);
}

void SimpleTexture::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void SimpleTexture::draw(float offset){
	//draw(float x, float y, float w, float h);
	EverTexture::draw(x, y + offset, width, height);
}

SimpleTexture::~SimpleTexture(void)
{
}