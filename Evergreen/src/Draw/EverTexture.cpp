#include "EverTexture.h"

EverTexture::EverTexture(string src)
{
	loadTexture(src);
}

EverTexture::EverTexture(){

}

void EverTexture::loadTexture(string src){
	this->src = src;
	image.loadImage(src);
	width = image.width;
	height = image.height;

	ofLoadImage(texture, src);
}

void EverTexture::draw(float offset){
	printf("IMPLEMENT THIS FUNCTION");
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

void EverTexture::drawTexture(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4){
	ofSetColor(255);
	texture.bind();

	// texture coordinates go CW
	glBegin(GL_QUADS);
				
		glVertex3f(p4.x, p4.y, 0);
		glTexCoord2f(width, height);
				
		glVertex3f(p2.x, p2.y, 0);
		glTexCoord2f(0, height);
				
		glVertex3f(p1.x, p1.y, 0);
		glTexCoord2f(0.0f, 0.0f);
				
		glVertex3f(p3.x, p3.y, 0);
		glTexCoord2f(width, 0.0f);

	glEnd();

	texture.unbind();
	ofNoFill();
	//ofRect(p1, p4.x-p1.x, p4.y-p1.y); // DEBUG
}

EverTexture::~EverTexture(void)
{
}
