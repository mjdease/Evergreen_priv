#include "EverFlower.h"

EverFlower::EverFlower(ofPoint position)
{
	flower = new EverTexture("environment/foreground/flower.png");
	flower_width = 0;
	flower_height = 0;
	this->position = position;
	MAX_SIZE = ofPoint(flower->getWidth(), flower->getHeight());
}

void EverFlower::draw(float height) {
	if(flower_width < MAX_SIZE.x && flower_height < MAX_SIZE.y) {
		flower_width += 7;
		flower_height += 7;
	}

	flower->draw(position.x - (flower_width / 2),position.y - (flower_height / 2),flower_width,flower_height);
}

EverFlower::~EverFlower(void)
{
}