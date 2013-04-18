#include "GrassTexture.h"

GrassTexture::GrassTexture(string src):EverTexture(src)
{
	loadTexture(src);
}

void GrassTexture::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void GrassTexture::draw(){
	//draw(float x, float y, float w, float h);
	EverTexture::draw(x, y, width, height);
}

GrassTexture::~GrassTexture(void)
{
}