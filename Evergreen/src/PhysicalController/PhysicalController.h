#pragma once
#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include "QuadEncoder.h"

class PhysicalController{
public:
	PhysicalController();
	void PhysicalController::init(string serial);
	void PhysicalController::updateArduino();
	//true only when button changes from up to down -- will be true only once per button press
	bool PhysicalController::getButtonPress();
	//-1, 0, 1 -> + is scrolling down, - is scrolling up.
	int PhysicalController::getScroll();
	//0..1 magnitude of the wind blowing in from the left side
	float PhysicalController::getLeftWind();
	//0..1 magnitude of the wind blowing in from the right side
	float PhysicalController::getRightWind();
	//0..1 magnitude of the sunniness
	float PhysicalController::getSunniness();
	//0..1 magnitude of the shakiness
	float PhysicalController::getShakiness();
	//0 - nothing, stuff should die. 1 - grass. 2 - flowers. 3 - thorn bushes.
	int PhysicalController::getPlantType();

	//DEBUG
	void PhysicalController::debugKeyPress(int key);
	void PhysicalController::debugKeyReleased(int key);

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
	int buttonLedState, buttonState, pButtonState, pLeftReedVal, pRightReedVal, plantType;
	char wheelChange;
	long lastButtonChangeTime, debounceDelay, pLeftTime, pRightTime;
	float leftWind, rightWind, sunniness, shakiness;

	void PhysicalController::setupArduino(const int & version);
	void PhysicalController::digitalPinChanged(const int & pinNum);
	float PhysicalController::msToMin(float millliseconds);
	float PhysicalController::constrain(float x, float low, float high);
	
	//DEBUG
	bool isKeyDown;
};

