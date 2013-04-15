#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"

class PhysicalController{
public:
	PhysicalController();
	void PhysicalController::init(string device_main, string device_sun, string device_ground);
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
	ofxSimpleSerial ardMain;
	ofxSimpleSerial ardSun;
	ofxSimpleSerial ardGround;

	bool isReady, isButtonUniquePress;
	int wheelChange, plantType;
	float leftWind, rightWind, sunniness, shakiness;

	void PhysicalController::onNewMessage(string & message);
	
	//DEBUG
	bool isKeyDown;
};

