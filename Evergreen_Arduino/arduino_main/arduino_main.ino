#include <Button.h>
#include <QuadEncoder.h>

#define BTN_LED 4
#define BTN_PIN 5
#define ROTARY_PIN1 6
#define ROTARY_PIN2 7
#define REED_PIN_LEFT 8
#define REED_PIN_RIGHT 9

#define BUTTON "b:"
#define WHEEL "w:"
#define WIND_LEFT "l:"
#define WIND_RIGHT "r:"

int wheelChange = 0;
long pLeftTime = 0;
long pRightTime = 0;

QuadEncoder qe(ROTARY_PIN1,ROTARY_PIN2);
Button button = Button(BTN_PIN, PULLUP);
//reed switches can be used just like buttons.
Button lWindmill = Button(REED_PIN_LEFT, PULLDOWN);
Button rWindmill = Button(REED_PIN_RIGHT, PULLDOWN);

void setup(){
  pinMode(BTN_LED, OUTPUT);
  
  Serial.begin(115200);  
}

void loop()
{
  wheelChange=qe.tick();
  
  //BUTTON
  if (button.uniquePress()){
    digitalWrite(BTN_LED, LOW);  // turn the button LED off
    Serial.print(BUTTON);
    Serial.println(1);
  }
  else if(!button.isPressed()){
    digitalWrite(BTN_LED, HIGH);  // turn the button LED on
  }
  
  //SCROLL WHEEL
  if (wheelChange=='>'){
    Serial.print(WHEEL);
    Serial.println('+');
  }
  else if (wheelChange=='<'){
    Serial.print(WHEEL);
    Serial.println('-');
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
        int rpm = (int)(1 / msToMin(leftTime - pLeftTime));
        Serial.print(WIND_LEFT);
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
        int rpm = (int)(1 / msToMin(rightTime - pRightTime));
        Serial.print(WIND_RIGHT);
        Serial.println(rpm);
        pRightTime = rightTime;
      }
    }
    else{
      pRightTime = millis();
    }
  }
  
  delay(5);
  return;
}

float msToMin(float millliseconds){
  return (millliseconds / 1000.0 / 60.0); 
}


