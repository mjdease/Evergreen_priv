#pragma once
#include "ofMain.h"

class PhysicalController{
public:
	PhysicalController(string serial);

private:
	ofArduino ard;
	bool isSetup;

	void PhysicalController::setupArduino(const int & version);
	void PhysicalController::updateArduino();
};

