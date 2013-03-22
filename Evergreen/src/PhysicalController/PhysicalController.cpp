#include "PhysicalController.h"

PhysicalController::PhysicalController(){

}

PhysicalController::PhysicalController(string serial){
	buttonLedState = ARD_HIGH;
	pButtonState = ARD_HIGH;
	lastButtonChangeTime = 0;
	debounceDelay = 50;
	wheelChange = '-';
	pLeftReedVal = 0;
	pRightReedVal = 0;
	pLeftTime = 0;
	pRightTime = 0;
	leftWind = 0;
	rightWind = 0;

	isButtonPressed = false;
	isButtonEvent = false;

	isSetup	= false;
}

void PhysicalController::init(){
	ard.connect("COM4", 57600);

	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &PhysicalController::setupArduino);
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

	wheel = QuadEncoder(&ard, rotaryPin1, rotaryPin2);

	ofAddListener(ard.EDigitalPinChanged, this, &PhysicalController::digitalPinChanged);
}

void PhysicalController::updateArduino(){
	// update the arduino, get any data or messages.
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (isSetup) {
		ard.sendDigital(buttonLedPin, buttonLedState);
		wheelChange = wheel.tick();

		int leftReedVal = ard.getDigital(windLeftPin);
		int rightReedVal = ard.getDigital(windRightPin);

		if(leftReedVal == 1 && pLeftReedVal == 0){
			if(pLeftTime != 0){
				long leftTime = ofGetElapsedTimeMillis();
				if(leftTime - pLeftTime > 2000){//ignore changes greater than 2s apart
					pLeftTime = 0;
				}
				else{
					//half rotation distance over the time it took
					//typical rpm values will be between 100 - 300 with some noise (averaging will be needed)
					float rpm = 0.5 / msToMin(leftTime - pLeftTime);
					leftWind = constrain(rpm / 350, 0, 1);
					pLeftTime = leftTime;
				}
			}
			else{
				pLeftTime = ofGetElapsedTimeMillis();
			}
		}

		if(rightReedVal == 1 && pRightReedVal == 0){
			if(pLeftTime != 0){
				long rightTime = ofGetElapsedTimeMillis();
				if(rightTime - pRightTime > 2000){//ignore changes greater than 2s apart
					pRightTime = 0;
				}
				else{
					//half rotation distance over the time it took
					//typical rpm values will be between 100 - 300 with some noise (averaging will be needed)
					float rpm = 0.5 / msToMin(rightTime - pRightTime);
					rightWind = constrain(rpm / 350, 0, 1);
					pLeftTime = rightTime;
				}
			}
			else{
				pRightTime = ofGetElapsedTimeMillis();
			}
		}


		pLeftReedVal = leftReedVal;
		pRightReedVal = rightReedVal;
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
	switch(wheelChange){
	case '-':
		return 0;
	case '<':
		return -1;
	case '>':
		return 1;
	default:
		return 0;
	}
}
//0..1 magnitude of the wind blowing in from the left side
float PhysicalController::getLeftWind(){
	if(pLeftTime - ofGetElapsedTimeMillis() > 2000){
		return 0;
	}
	return leftWind;
}
//0..1 magnitude of the wind blowing in from the right side
float PhysicalController::getRightWind(){
	if(pRightTime - ofGetElapsedTimeMillis() > 2000){
		return 0;
	}
	return rightWind;
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
				buttonLedState = ARD_HIGH;
			}
			if(reading == ARD_HIGH){
				isButtonPressed = false;
				buttonLedState = ARD_LOW;
			}
		}
		break;
	}
}

//Utils
float PhysicalController::msToMin(float millliseconds){
  return (millliseconds / 1000.0 / 60.0); 
}

float PhysicalController::constrain(float x, float low, float high) {  
    return x < low ? low : x > high ? high : x;  
} 