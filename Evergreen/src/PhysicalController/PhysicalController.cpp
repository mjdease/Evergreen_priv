#include "PhysicalController.h"

//enable keybard input & logging
#define DEBUG true

//may disable some arduinos here
#define HAS_ARDUINO_MAIN true
#define HAS_ARDUINO_SUN true
#define HAS_ARDUINO_GROUND true

//input sources
#define BUTTON 'b'
#define WHEEL 'w'
#define WIND_LEFT 'l'
#define WIND_RIGHT 'r'
#define SUN 's'
#define SHAKE 'k'
#define PLANT 'p'

PhysicalController::PhysicalController(){
	wheelChange = 0;
	leftWind = 0.0;
	rightWind = 0.0;
	sunniness = 0.0;
	shakiness = 0.0;
	plantType = 0;
	isButtonUniquePress = false;

	isReady	= false;

	//INIT DEBUG
	if(DEBUG){
		isKeyDown = false;
	}
}

void PhysicalController::init(string device_main, string device_sun, string device_ground){
	bool success = true;
	if(HAS_ARDUINO_MAIN){
		if(ardMain.setup(device_main, 115200)){
			ardMain.startContinuesRead();
			ofAddListener(ardMain.NEW_MESSAGE, this, &PhysicalController::onNewMessage);
		}
		else {
			success = false;
			if(DEBUG){
				cout << "Can't connect to main arduino board" << endl;
			}
		}
	}
	if(HAS_ARDUINO_SUN){
		if(ardSun.setup(device_sun, 115200)){
			ardSun.startContinuesRead();
			ofAddListener(ardSun.NEW_MESSAGE, this, &PhysicalController::onNewMessage);
		}
		else {
			success = false;
			if(DEBUG){
				cout << "Can't connect to sun arduino board" << endl;
			}
		}
	}
	if(HAS_ARDUINO_GROUND){
		if(ardGround.setup(device_ground, 115200)){
			ardGround.startContinuesRead();
			ofAddListener(ardGround.NEW_MESSAGE, this, &PhysicalController::onNewMessage);
		}
		else {
			success = false;
			if(DEBUG){
				cout << "Can't connect to ground arduino board" << endl;
			}
		}
	}
	isReady = success;
}

void PhysicalController::updateArduino(){
	if (!DEBUG && isReady) {
		if(leftWind > 0.0){
			leftWind -= 0.01;
			if(leftWind < 0.0) leftWind = 0.0;
		}
		if(rightWind > 0.0){
			rightWind -= 0.01;
			if(rightWind < 0.0) rightWind = 0.0;
		}
		if(sunniness > 0.0){
			sunniness -= 0.01;
			if(sunniness < 0.0) sunniness = 0.0;
		}
		if(shakiness > 0.0){
			shakiness -= 0.005;
			if(shakiness < 0.0) shakiness = 0.0;
		}
	}
	else if(DEBUG){
		if(!isKeyDown){
			rightWind = ofClamp(rightWind -= 0.005, 0, 1);
			leftWind = ofClamp(leftWind -= 0.005, 0, 1);
			sunniness = ofClamp(sunniness -= 0.001, 0, 1);
			shakiness = ofClamp(shakiness -= 0.01, 0, 1);
		}
	}
}


//Call every 100ms with a value 0 - 100. 
//0 means totally sunny, 50 is very heavy clouds (no rain), 100 is very heavy rain.
void PhysicalController::setWeather(int state){
	float val = (float)state / 100.0f;
	string message = "t" + ofToString(val);
	ardMain.writeString(message);
}

//true only when button changes from up to down -- will be true only once per button press
bool PhysicalController::getButtonPress(){
	if(isButtonUniquePress){
		isButtonUniquePress = false;
		return true;
	}
	return false;
}

//any integer, sign indicates direction -> + is scrolling down, - is scrolling up.
//a quick flick of the wheel generates ~4 step changes (so +/-4) - may want to scale this value to reduce sensitivity
int PhysicalController::getScroll(){
	int val = wheelChange;
	wheelChange = 0;
	return val;
}

//0..1 magnitude of the wind blowing in from the left side
float* PhysicalController::getLeftWind(){
	return &leftWind;
}

//0..1 magnitude of the wind blowing in from the right side
float* PhysicalController::getRightWind(){
	return &rightWind;
}

//0..1 magnitude of the sunniness
float* PhysicalController::getSunniness(){
	return &sunniness;
}

//0..1 magnitude of the shakiness
float* PhysicalController::getShakiness(){
	return &shakiness;
}

//0 - nothing, stuff should die. 1 - grass. 2 - flowers. 3 - thorn bushes.
int* PhysicalController::getPlantType(){
	return &plantType;
}



void PhysicalController::onNewMessage(string & message){
	if(DEBUG){
		cout << "INPUT: " << message << endl;
	}
	vector<string> input = ofSplitString(message, ":");
	char type = ofToChar(input.at(0));
	switch(type){
	case BUTTON:
		if(ofToBool(input.at(1))){
			isButtonUniquePress = true;
		}
		break;
	case WHEEL:{
		char dir = ofToChar(input.at(1));
		wheelChange += (dir == '+') ? 1 : (dir == '-') ? -1 : 0;
		break;}
	case WIND_LEFT:
		leftWind = ofClamp(ofMap(ofToFloat(input.at(1)), 0, 300, 0.0, 1.0), 0.0, 1.0);
		break;
	case WIND_RIGHT:
		rightWind = ofClamp(ofMap(ofToFloat(input.at(1)), 0, 300, 0.0, 1.0), 0.0, 1.0);
		break;
	case SUN:
		sunniness = ofClamp(ofMap(ofToFloat(input.at(1)), 0, 5, 0.0, 1.0), 0.0, 1.0);
		break;
	case SHAKE:
		shakiness = ofClamp(ofMap(ofToFloat(input.at(1)), 0, 150, 0.0, 1.0), 0.0, 1.0);
		break;
	case PLANT:
		plantType = ofToInt(input.at(1));
		break;
	}
}

//DEBUG
void PhysicalController::debugKeyPress(int key){
	if(!DEBUG) return;
	isKeyDown = true;
	switch(key){
	case OF_KEY_UP:
		wheelChange++;
		break;
	case OF_KEY_DOWN:
		wheelChange--;
		break;
	case OF_KEY_RETURN:
		isButtonUniquePress = true;
		break;
	case OF_KEY_RIGHT:
		leftWind = ofClamp(leftWind += 0.01, 0, 1);
		break;
	case OF_KEY_LEFT:
		rightWind = ofClamp(rightWind += 0.01, 0, 1);
		break;
	case OF_KEY_F1:
		sunniness = ofClamp(sunniness += 0.01, 0, 1);
		break;
	case OF_KEY_F2:
		shakiness = ofClamp(shakiness += 0.01, 0, 1);
		break;
	case OF_KEY_F3:
		plantType += 1;
		plantType %= 4;
		break;
	case OF_KEY_F4:
		PhysicalController::setWeather(ofRandom(1.0));
		break;
	}
}

void PhysicalController::debugKeyReleased(int key){
	if(!DEBUG) return;
	isKeyDown = false;
}