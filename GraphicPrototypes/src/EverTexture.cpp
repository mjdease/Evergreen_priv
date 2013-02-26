#include "EverTexture.h"

EverTexture::EverTexture(string src)
{
	setImage(src);
}

void EverTexture::setImage(string src){
	this->src = src;
	image.loadImage(src);
}

void EverTexture::draw(float x, float y){
	image.draw(x, y);
}
void EverTexture::draw(float x, float y, float w, float h){
	image.draw(x, y, w, h);
}
void EverTexture::draw(float x, float y, float w, float h, float rotation){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	image.draw(-w/2, -h/2, w, h);
	glPopMatrix();
}
void EverTexture::draw(float x, float y, float rotation){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	image.draw(-image.width/2, -image.height/2);
	glPopMatrix();

	/*ofPushMatrix();
	ofTranslate(x, y);
	ofRotate(rotation);
	image.draw(-image.width/2, -image.height/2);
	ofPopMatrix();*/
}

EverTexture::~EverTexture(void)
{
}
