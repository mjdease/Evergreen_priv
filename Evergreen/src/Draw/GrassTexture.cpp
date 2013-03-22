#include "GrassTexture.h"

GrassTexture::GrassTexture(string src):EverTexture(src)
{
	loadTexture(src);
}

void GrassTexture::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void GrassTexture::draw(float offset){
	//draw(float x, float y, float w, float h);
	EverTexture::draw(x, y + offset, width, height);
}

GrassTexture::~GrassTexture(void)
{
}