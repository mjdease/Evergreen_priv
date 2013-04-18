#include "EverEnvironment.h"

void EverEnvironment::update(){

}

EverEnvironment::EverEnvironment(PhysicalController* controller, EverTree* tree, EverGround* ground)
{
	ctrl = controller;
	this->tree = tree;
	this->ground = ground;
}


EverEnvironment::~EverEnvironment(void)
{
}
