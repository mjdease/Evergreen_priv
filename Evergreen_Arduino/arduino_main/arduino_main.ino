#include <Button.h>
#include <QuadEncoder.h>

const int buttonLedPin =  4; 
const int buttonPin = 5;  
const int rotaryPin1 =  6; 
const int rotaryPin2 = 7;  
const int windLeftPin = 8; 
const int windRightPin = 9;  

int qe1Move = 0;
long pLeftTime = 0;
long pRightTime = 0;

QuadEncoder qe(rotaryPin1,rotaryPin2);
Button button = Button(5, PULLUP);
Button lWindmill = Button(8, PULLDOWN);
Button rWindmill = Button(9, PULLDOWN);

void setup(){
  pinMode(buttonLedPin, OUTPUT);
  
  Serial.begin(9600);  
}


void loop()
{
  qe1Move=qe.tick();
  
  //BUTTON
  if (button.uniquePress()){
    digitalWrite(buttonLedPin, LOW);  // turn the LED off
    Serial.println("button pushed");
  }
  else if(!button.isPressed()){
    digitalWrite(buttonLedPin, HIGH);  // turn the LED on
  }
  
  //SCROLL WHEEL
  if (qe1Move=='>'){
    Serial.print(char(qe1Move));
  }
  else if (qe1Move=='<'){
    Serial.print(char(qe1Move));
  }
  
  //LEFT WINDMILL
  if (lWindmill.uniquePress()){
    if(pLeftTime != 0){
      unsigned long leftTime = millis();
      if(leftTime - pLeftTime > 1000){//ignore changes greater than 2s apart
        pLeftTime = 0;
      }
      else{
        //1 rotation over time it took
        //typical rpm values will be between 100 - 300
        float rpm = 1 / msToMin(leftTime - pLeftTime);
        Serial.print("left rpm: ");
        Serial.println(rpm);
        pLeftTime = leftTime;
      }
    }
    else{
      pLeftTime = millis();
    }
  }
  
  //RIGHT WINDMILL
  if (rWindmill.uniquePress()){
    if(pRightTime != 0){
      long rightTime = millis();
      if(rightTime - pRightTime > 1000){//ignore changes greater than 1s apart
        pRightTime = 0;
      }
      else{
        //1 rotation over time it took
        //typical rpm values will be between 100 - 300
        float rpm = 1 / msToMin(rightTime - pRightTime);
        Serial.print("right rpm: ");
        Serial.println(rpm);
        pRightTime = rightTime;
      }
    }
    else{
      pRightTime = millis();
    }
  }
  
  delay(1);
  return;
}

float msToMin(float millliseconds){
  return (millliseconds / 1000.0 / 60.0); 
}


