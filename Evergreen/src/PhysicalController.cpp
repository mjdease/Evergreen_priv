#include "PhysicalController.h"

PhysicalController::PhysicalController(){
	
}

PhysicalController::PhysicalController(string serial){
	buttonLedState = ARD_HIGH;
	pButtonState = ARD_HIGH;
	lastButtonChangeTime = 0;
	debounceDelay = 50;
	
	isButtonPressed = false;
	isButtonEvent = false;

	ard.connect(serial, 57600);

	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &PhysicalController::setupArduino);
	isSetup	= false;
}

void PhysicalController::setupArduino(const int & version){
	ofRemoveListener(ard.EInitialized, this, &PhysicalController::setupArduino);
    isSetup = true;
    
    // print firmware name and version to the console
    cout << ard.getFirmwareName() << endl; 
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
	
	ard.sendDigitalPinMode(buttonLedPin, ARD_OUTPUT);
	ard.sendDigitalPinMode(buttonPin, ARD_INPUT);
	ard.sendDigitalPinMode(windLeftPin, ARD_INPUT);
	ard.sendDigitalPinMode(windRightPin, ARD_INPUT);

	ofAddListener(ard.EDigitalPinChanged, this, &PhysicalController::digitalPinChanged);
}

void PhysicalController::updateArduino(){
	// update the arduino, get any data or messages.
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (isSetup) {
        // do stuff here
	}
}

//true only when button changes from up to down -- will be true only once per button press
bool PhysicalController::getButtonPress(){
	if(isButtonEvent){
		isButtonEvent = false;
		return true;
	}
	return false;
}
//any integer, sign indicates direction -> + is scrolling down, - is scrolling up.
//a quick flick of the wheel generates ~8 step changes (so +/-8) - may want to scale this value to reduce sensitivity
int PhysicalController::getScroll(){
	return 5;
}
//0..1 magnitude of the wind blowing in from the left side
float PhysicalController::getLeftWind(){
	return 0.1;
}
//0..1 magnitude of the wind blowing in from the right side
float PhysicalController::getRightWind(){
	return 0.1;
}

void PhysicalController::digitalPinChanged(const int & pinNum) {
    //cout << "digital pin: " + ofToString(pinNum) << endl; 
	switch(pinNum){
	case buttonPin:
		int reading = ard.getDigital(buttonPin);
 
		if ((ofGetElapsedTimeMillis() - lastButtonChangeTime) > debounceDelay) {
			buttonState = reading;
			lastButtonChangeTime = ofGetElapsedTimeMillis();
			if(reading == ARD_LOW){
				isButtonEvent = true;
				isButtonPressed = true;
				ard.sendDigital(buttonLedPin, ARD_HIGH);
			}
			if(reading == ARD_HIGH){
				isButtonPressed = false;
				ard.sendDigital(buttonLedPin, ARD_LOW);
			}
		}
		break;
	}
}
