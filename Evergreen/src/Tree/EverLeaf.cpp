#include "EverLeaf.h"

SimpleTexture* EverLeaf::leaf1 = NULL;
SimpleTexture* EverLeaf::leaf2 = NULL;
SimpleTexture* EverLeaf::leaf3 = NULL;
SimpleTexture* EverLeaf::leaf4 = NULL;
SimpleTexture* EverLeaf::leaf5 = NULL;
SimpleTexture* EverLeaf::leaf6 = NULL;

EverLeaf::EverLeaf(void)
{
	loadImages();
}

void EverLeaf::loadImages(){
	if(leaf1 == NULL){
		leaf1 = new SimpleTexture("tree/leaves/leaf01.png");
		leaf2 = new SimpleTexture("tree/leaves/leaf02.png");
		leaf3 = new SimpleTexture("tree/leaves/leaf03.png");
		leaf4 = new SimpleTexture("tree/leaves/leaf04.png");
		leaf5 = new SimpleTexture("tree/leaves/leaf05.png");
		leaf6 = new SimpleTexture("tree/leaves/leaf06.png");
	}
}


EverLeaf::~EverLeaf(void)
{
}
