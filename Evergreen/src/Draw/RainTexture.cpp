#include "RainTexture.h"

RainTexture::RainTexture()
{
	width = height = -1;
	x = y = 0;
	loadImages();
	frame = 0;
}

void RainTexture::setAmount(float amount){
	rainAmount = amount;
}

void RainTexture::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void RainTexture::setSize(int width, int height){
	this->width = width;
	this->height = height;
}

void RainTexture::update(){
	if(ofGetFrameNum()%5 == 3){
		frame += 1;
		frame %= 6;
	}
}

void RainTexture::drawDroplets(int x, int y){
	droplets[frame/2]->setOpacity((rainAmount) * 5);
	droplets[frame/2]->draw(x,y-dropletHeight);
}

void RainTexture::draw(){
	rain[frame]->setOpacity((rainAmount)*5);
	rain[frame]->draw(x,y);
	rain[frame]->draw(x,y + height);
	rain[frame]->draw(x,y + height*2);
}

void RainTexture::drawMidground(){
	if(rainAmount > 50){
		rain[((frame+1)%3)]->setOpacity((rainAmount - 50)*5);
		rain[((frame+1)%3)]->draw(x,y);
		rain[((frame+1)%3)]->draw(x,y + height);
		rain[((frame+1)%3)]->draw(x,y + height*2);
	}
}

void RainTexture::loadImages(){
	rain[0] = new EverTexture();
	rain[1] = new EverTexture();
	rain[2] = new EverTexture();
	rain[3] = new EverTexture();
	rain[4] = new EverTexture();
	rain[5] = new EverTexture();

	rain[0]->loadTexture("environment/foreground/rain/rain_angled_01.png");
	rain[1]->loadTexture("environment/foreground/rain/rain_angled_02.png");
	rain[2]->loadTexture("environment/foreground/rain/rain_angled_03.png");
	rain[3]->loadTexture("environment/foreground/rain/rain_angled_04.png");
	rain[4]->loadTexture("environment/foreground/rain/rain_angled_05.png");
	rain[5]->loadTexture("environment/foreground/rain/rain_angled_06.png");

	setSize(rain[0]->getWidth(), rain[0]->getHeight());
	
	droplets[0] = new EverTexture();
	droplets[1] = new EverTexture();
	droplets[2] = new EverTexture();

	droplets[0]->loadTexture("environment/foreground/rain/droplets_01.png");
	droplets[1]->loadTexture("environment/foreground/rain/droplets_02.png");
	droplets[2]->loadTexture("environment/foreground/rain/droplets_03.png");
	dropletHeight = droplets[0]->getHeight();
}

RainTexture::~RainTexture(void)
{
}