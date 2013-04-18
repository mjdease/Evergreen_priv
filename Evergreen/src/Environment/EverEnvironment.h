#pragma once
#include "../PhysicalController/PhysicalController.h"
#include "../Tree/EverTree.h"
#include "EverGround.h"

class EverEnvironment
{
public:
	void update();

	EverEnvironment(PhysicalController* controller, EverTree* tree, EverGround* ground);
	~EverEnvironment(void);

private:
	PhysicalController* ctrl;
	EverTree* tree;
	EverGround* ground;
	
};

