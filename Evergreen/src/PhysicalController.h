#pragma once
#include "ofMain.h"

class PhysicalController{
public:
	PhysicalController(string serial);
	void PhysicalController::updateArduino();
	//true only when button changes from up to down -- will be true only once per button press
	bool PhysicalController::getButtonPress();
	//any integer, sign indicates direction -> + is scrolling down, - is scrolling up.
	//a quick flick of the wheel generates ~8 step changes (so +/-8) - may want to scale this value to reduce sensitivity
	int PhysicalController::getScroll();
	//0..1 magnitude of the wind blowing in from the left side
	float PhysicalController::getLeftWind();
	//0..1 magnitude of the wind blowing in from the right side
	float PhysicalController::getRightWind();

private:
	ofArduino ard;
	bool isSetup;

	void PhysicalController::setupArduino(const int & version);
};

