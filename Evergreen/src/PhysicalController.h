#pragma once
#include "ofMain.h"

class PhysicalController{
public:
	PhysicalController(string serial);
	void PhysicalController::updateArduino();

private:
	ofArduino ard;
	bool isSetup;

	void PhysicalController::setupArduino(const int & version);
};

