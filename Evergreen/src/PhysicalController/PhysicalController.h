#pragma once
#include "ofMain.h"
#include "QuadEncoder.h"

class PhysicalController{
public:
	PhysicalController();
	PhysicalController(string serial);
	void PhysicalController::init();
	void PhysicalController::updateArduino();
	//true only when button changes from up to down -- will be true only once per button press
	bool PhysicalController::getButtonPress();
	//-1, 0, 1 -> + is scrolling down, - is scrolling up.
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
	QuadEncoder wheel;

	bool isSetup, isButtonPressed, isButtonEvent;
	int buttonLedState, buttonState, pButtonState, pLeftReedVal, pRightReedVal;
	char wheelChange;
	long lastButtonChangeTime, debounceDelay, pLeftTime, pRightTime;
	float leftWind, rightWind;

	void PhysicalController::setupArduino(const int & version);
	void PhysicalController::digitalPinChanged(const int & pinNum);
	float PhysicalController::msToMin(float millliseconds);
	float PhysicalController::constrain(float x, float low, float high);
};

