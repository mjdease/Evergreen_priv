#include "EverLeaf.h"

SimpleTexture* EverLeaf::leaf1 = NULL;
SimpleTexture* EverLeaf::leaf2 = NULL;
SimpleTexture* EverLeaf::leaf3 = NULL;
SimpleTexture* EverLeaf::leaf4 = NULL;
SimpleTexture* EverLeaf::leaf5 = NULL;
SimpleTexture* EverLeaf::leaf6 = NULL;

EverLeaf::EverLeaf(int leafType)
{
	width = height = 0;
	loadImages(leafType);
}

void EverLeaf::setPosition(float length){
	this->length = length;
	drawLeaf->setPosition(0,length);
}

void EverLeaf::update(){
	width = width + (oWidth - width)/10;
	height = height + (oHeight - height)/10;
}

void EverLeaf::draw(){
	drawLeaf->draw(width, height);
}

void EverLeaf::loadImages(int leafType){
	if(leaf1 == NULL){
		leaf1 = new SimpleTexture("tree/leaves/leaf01.png");
		leaf2 = new SimpleTexture("tree/leaves/leaf02.png");
		leaf3 = new SimpleTexture("tree/leaves/leaf03.png");
		leaf4 = new SimpleTexture("tree/leaves/leaf04.png");
		leaf5 = new SimpleTexture("tree/leaves/leaf05.png");
		leaf6 = new SimpleTexture("tree/leaves/leaf06.png");

		leaf5->setSize(leaf5->getWidth()/2,leaf5->getHeight()/2);
	}
	
	if(leafType == 1){
		drawLeaf = leaf1;
	}
	else if(leafType == 2){
		drawLeaf = leaf2;
	}
	else if(leafType == 3){
		drawLeaf = leaf3;
	}
	else if(leafType == 4){
		drawLeaf = leaf4;
	}
	else if(leafType == 5){
		drawLeaf = leaf5;
	}
	else{
		drawLeaf = leaf6;
	}

	oWidth = drawLeaf->getWidth();
	oHeight = drawLeaf->getHeight();
}


EverLeaf::~EverLeaf(void)
{
}
