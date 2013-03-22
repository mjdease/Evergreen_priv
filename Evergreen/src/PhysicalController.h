#pragma once
#include "ofMain.h"

class PhysicalController{
public:
	PhysicalController();
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
	static const int buttonLedPin = 4;
	static const int buttonPin = 5;
	static const int rotaryPin1 = 6;
	static const int rotaryPin2 = 7;
	static const int windLeftPin = 8;
	static const int windRightPin = 9;

	ofArduino ard;
	bool isSetup, isButtonPressed, isButtonEvent;
	int buttonLedState, buttonState, pButtonState;
	long lastButtonChangeTime, debounceDelay;

	void PhysicalController::setupArduino(const int & version);
	void PhysicalController::digitalPinChanged(const int & pinNum);
};

