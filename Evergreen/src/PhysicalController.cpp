#include "PhysicalController.h"

PhysicalController::PhysicalController(string serial){
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
}

void PhysicalController::updateArduino(){
	// update the arduino, get any data or messages.
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (isSetup) {
        // do stuff here
	}
}
