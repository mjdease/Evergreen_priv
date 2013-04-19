#include "SimpleTexture.h"

SimpleTexture::SimpleTexture(string src):EverTexture(src)
{
	loadTexture(src);
	width = height = -1;
}

void SimpleTexture::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void SimpleTexture::setSize(int width, int height){
	this->width = width;
	this->height = height;
}

void SimpleTexture::draw(){
	if(width == -1){
		EverTexture::draw(x, y);
		return;
	}
	EverTexture::draw(x, y, width, height);
}

void SimpleTexture::draw(float width, float height){
	EverTexture::draw(x, y, width, height);
}

SimpleTexture::~SimpleTexture(void)
{
}