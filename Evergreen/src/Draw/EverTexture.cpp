#include "EverTexture.h"

EverTexture::EverTexture(string src):opacity(255)
{
	loadTexture(src);
}

EverTexture::EverTexture():opacity(255){

}

void EverTexture::loadTexture(string src){

	ofDisableArbTex();

	this->src = src;
	ofImage img(src);
	width = img.width;
	height = img.height;

	texture = img.getTextureReference();
	texture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

	texture.bind();
	glGenerateMipmap(GL_TEXTURE_2D);
	texture.unbind();


	//ofLoadImage(texture, src);
}



void EverTexture::draw(float offset){
	printf("IMPLEMENT THIS FUNCTION");
}

void EverTexture::draw(float x, float y){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	texture.draw(x, y);
	ofDisableAlphaBlending();
}
void EverTexture::draw(float x, float y, float w, float h){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	texture.draw(x, y, w, h);
	ofDisableAlphaBlending();
}
void EverTexture::draw(float x, float y, float w, float h, float rotation){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	texture.draw(-w/2, -h/2, w, h);
	glPopMatrix();
	ofDisableAlphaBlending();
}
void EverTexture::draw(float x, float y, float rotation){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	texture.draw(-width/2, -height/2);
	glPopMatrix();
	ofDisableAlphaBlending();

	/*ofPushMatrix();
	ofTranslate(x, y);
	ofRotate(rotation);
	image.draw(-image.width/2, -image.height/2);
	ofPopMatrix();*/
}

void EverTexture::drawTexture(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	texture.bind();
	//image.getTextureReference().bind();
	// texture coordinates go CW
	glBegin(GL_QUADS);
				
		glVertex3f(p4.x, p4.y, 0);
		glTexCoord2f(1.0f, 1.0f);
				
		glVertex3f(p2.x, p2.y, 0);
		glTexCoord2f(0.0f, 1.0f);
				
		glVertex3f(p1.x, p1.y, 0);
		glTexCoord2f(0.0f, 0.0f);
				
		glVertex3f(p3.x, p3.y, 0);
		glTexCoord2f(1.0f, 0.0f);

	glEnd();


	texture.unbind();
	//image.getTextureReference().unbind();
	ofDisableAlphaBlending();
}

void EverTexture::setOpacity(float alpha){
	opacity = alpha;
}

float EverTexture::getWidth(){
	return width;
}

float EverTexture::getHeight(){
	return height;
}

EverTexture::~EverTexture(void)
{
}
