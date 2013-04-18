#include "EverPlant.h"
EverTexture* EverPlant::thornTexture = NULL;
EverTexture* EverPlant::flowerTexture = NULL;

EverPlant::EverPlant(ofPoint position, bool thorn)
{
	if(thornTexture == NULL){
		flowerTexture = new EverTexture("environment/foreground/plants/flowers.png");
		thornTexture = new EverTexture("environment/foreground/plants/thornbush.png");
	}
	
	plantWidth = plantHeight = 1;

	deleteMe = false;
	
	this->position = position;

	float tempRand = ofRandomuf()*0.5 + 0.5;

	this->thorn = thorn;

	if(thorn == true)
		MAX_SIZE = ofPoint(thornTexture->getWidth()*tempRand, thornTexture->getHeight()*tempRand);
	else
		MAX_SIZE = ofPoint(flowerTexture->getWidth()*tempRand, flowerTexture->getHeight()*tempRand);
}

void EverPlant::erase(){
	MAX_SIZE.x = MAX_SIZE.y = 0;
}

void EverPlant::draw() {
	plantWidth += (MAX_SIZE.x - plantWidth)/20;
	plantHeight += (MAX_SIZE.x - plantHeight)/20;
	
	if(thorn == true)
		thornTexture->draw(position.x - (plantWidth / 2), position.y - plantHeight, plantWidth, plantHeight);
	else
		flowerTexture->draw(position.x - (plantWidth / 2), position.y - (plantHeight / 2), plantWidth, plantHeight);

	if(plantWidth < 1 || plantHeight < 1){
		deleteMe == true;
	}
}

EverPlant::~EverPlant(void)
{
}