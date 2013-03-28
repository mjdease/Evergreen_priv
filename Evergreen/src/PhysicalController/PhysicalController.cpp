#define DEBUG false

#include "PhysicalController.h"

PhysicalController::PhysicalController(){
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
	sunniness = 0;
	shakiness = 0;
	plantType = 0;

	isButtonPressed = false;
	isButtonEvent = false;

	isSetup	= false;

	//INIT DEBUG
	if(DEBUG){
		isKeyDown = false;
	}
}

void PhysicalController::init(string serial){
	ard.connect(serial, 57600);

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
	if (!DEBUG && isSetup) {
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
	else if(DEBUG){
		if(!isKeyDown){
			wheelChange = '-';
			isButtonPressed = false;
			buttonLedState = ARD_LOW;
			rightWind = constrain(rightWind -= 0.005, 0, 1);
			leftWind = constrain(leftWind -= 0.005, 0, 1);
			sunniness = constrain(sunniness -= 0.001, 0, 1);
			shakiness = constrain(shakiness -= 0.01, 0, 1);
		}
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
	if(!DEBUG && pLeftTime - ofGetElapsedTimeMillis() > 2000){
		return 0;
	}
	return leftWind;
}
//0..1 magnitude of the wind blowing in from the right side
float PhysicalController::getRightWind(){
	if(!DEBUG && pRightTime - ofGetElapsedTimeMillis() > 2000){
		return 0;
	}
	return rightWind;
}

//0..1 magnitude of the sunniness
float PhysicalController::getSunniness(){
	return sunniness;
}

//0..1 magnitude of the shakiness
float PhysicalController::getShakiness(){
	return shakiness;
}

//0 - nothing, stuff should die. 1 - grass. 2 - flowers. 3 - thorn bushes.
int PhysicalController::getPlantType(){
	return plantType;
}

void PhysicalController::digitalPinChanged(const int & pinNum) {
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

//DEBUG
void PhysicalController::debugKeyPress(int key){
	if(!DEBUG) return;
	isKeyDown = true;
	switch(key){
	case OF_KEY_UP:
		wheelChange = '<';
		break;
	case OF_KEY_DOWN:
		wheelChange = '>';
		break;
	case OF_KEY_RETURN:
		isButtonEvent = true;
		isButtonPressed = true;
		buttonLedState = ARD_HIGH;
		break;
	case OF_KEY_RIGHT:
		leftWind = constrain(leftWind += 0.01, 0, 1);
		break;
	case OF_KEY_LEFT:
		rightWind = constrain(rightWind += 0.01, 0, 1);
		break;
	case OF_KEY_F1:
		sunniness = constrain(sunniness += 0.01, 0, 1);
		break;
	case OF_KEY_F2:
		shakiness = constrain(shakiness += 0.01, 0, 1);
		break;
	case OF_KEY_F3:
		plantType += 1;
		plantType %= 4;
		break;
	}
}

void PhysicalController::debugKeyReleased(int key){
	if(!DEBUG) return;
	isKeyDown = false;
}