const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h> 

#define DEBUG false

#define NUM_REGISTERS 3 
#define NUM_LIGHTS 5
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255
#define TOUCH_THESHOLD 3

unsigned char pwmFrequency = 75;

struct Light {
  int led0;
  int led1;
  int led2;
  int sensor;
  int brightness;
  float brightnessScale;
  
  void init(){
    brightness = MIN_BRIGHTNESS * brightnessScale;
    ShiftPWM.SetOne(led0, brightness);
    ShiftPWM.SetOne(led1, brightness);
    ShiftPWM.SetOne(led2, brightness);
  }
  
  boolean sense(){
    boolean touched = false;
    if(readCapacitivePin(sensor) < TOUCH_THESHOLD){//no touch
      if(brightness > MIN_BRIGHTNESS * brightnessScale){
        brightness -= (6 * brightnessScale);
        if(brightness < MIN_BRIGHTNESS * brightnessScale) brightness = MIN_BRIGHTNESS * brightnessScale;
      }
    }
    else{//touch
      touched = true;
      if(brightness < MAX_BRIGHTNESS){
        brightness += (3 * brightnessScale);
        if(brightness > MAX_BRIGHTNESS) brightness = MAX_BRIGHTNESS;
      }
    }
    ShiftPWM.SetOne(led0, brightness);
    ShiftPWM.SetOne(led1, brightness);
    ShiftPWM.SetOne(led2, brightness);
    
    return touched;
  }
};

Light lights[] = {
  {0, 1, 2, 2, MIN_BRIGHTNESS, 1.0},//ne
  {3, 4, 7, 3, MIN_BRIGHTNESS, 1.0},//se
  {9, 10, 11, 4, MIN_BRIGHTNESS, 4.0},//c
  {12, 16, 17, 5, MIN_BRIGHTNESS, 1.0},//sw
  {18, 19, 20, 6, MIN_BRIGHTNESS, 1.0}//nw
};

void setup(){
  Serial.begin(115200);
  
  ShiftPWM.SetAmountOfRegisters(NUM_REGISTERS);
  
  ShiftPWM.Start(pwmFrequency,MAX_BRIGHTNESS);
  
  //sets initial brightness
  for(int i = 0; i < NUM_LIGHTS; i++){
    lights[i].init();
  }
}

void loop(){
  int sunniness = 0;
  
  if(DEBUG){
    Serial.print(readCapacitivePin(2));//ne
    Serial.print("\t");
    Serial.print(readCapacitivePin(3));//se
    Serial.print("\t");
    Serial.print(readCapacitivePin(4));//c
    Serial.print("\t");
    Serial.print(readCapacitivePin(5));//sw
    Serial.print("\t");
    Serial.println(readCapacitivePin(6));//nw
  }
  
  for(int i = 0; i < NUM_LIGHTS; i++){
    if(lights[i].sense()){
      sunniness++;
    }
  }
  
  Serial.println(sunniness);
  delay(10);
}


//The folowing code is from http://playground.arduino.cc/Code/CapacitiveSensor
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

