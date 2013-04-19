#include <LPD8806.h>
#include "SPI.h"
#include <Button.h>
#include <QuadEncoder.h>

#define WEATHER_INTERVAL 40

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

char wheelChange = 0;
unsigned long pLeftTime = 0;
unsigned long pRightTime = 0;
unsigned long pWeatherTime = 0;

float weather = 0.0f;

LPD8806 strip = LPD8806(64);

QuadEncoder qe(ROTARY_PIN1,ROTARY_PIN2);

Button button = Button(BTN_PIN, PULLUP);
//reed switches can be used just like buttons.
Button lWindmill = Button(REED_PIN_LEFT, PULLDOWN);
Button rWindmill = Button(REED_PIN_RIGHT, PULLDOWN);

int clouds[13] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62};
int rain[9][8] ={ {7, 6, 5, 4, 3, 2, 1, -1},
                  {8, 9, 10, 11, 12, 13, -1, -1},
                  {19, 18, 17, 16, 15, 14, -1, -1},
                  {20, 21, 22, 23, 24, -1, -1, -1},
                  {29, 28, 27, 26, -1, -1, -1, -1},
                  {30, 31, 32, 33, -1, -1, -1, -1},
                  {37, 36, 35, 34, -1, -1, -1, -1},
                  {38, 39, 40, 41, 42, -1, -1, -1},
                  {49, 48, 47, 46, 45, 44, -1, -1}
                };
int dropPosition[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
boolean activeDrop[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup(){
  pinMode(BTN_LED, OUTPUT);
  
  strip.begin();
  strip.show(); //all off
  
  Serial.begin(115200);  
}

void loop(){
  unsigned long time = millis();
  
  //WEATHER
  if(Serial.available()){
    if(Serial.read() == 't'){
      weather = Serial.parseFloat();
      Serial.println(weather);
    }
  }
  
  if(time - pWeatherTime > WEATHER_INTERVAL){
    pWeatherTime = time;
    if(weather <= 0.5){
      clearRain();
      resetRain();
    }
    if(weather == 0.0){
      clearClouds();
    }
    if(weather > 0.0){
      int base = (int)constrain(mapfloat(weather, 0.0, 0.5, 0.0, 30.0), 0, 30);
      for(int i = 0; i < 13; i++){
        int val = base + (int)random(-2 * weather, 5 * weather);
        strip.setPixelColor(clouds[i], strip.Color(val, val, val));
      }
    }
    if(weather > 0.5){
      int numDrops = constrain((int)mapfloat(weather, 0.5, 0.9, 1.0, 9.0), 0, 9);
      
      clearRain();
      
      for(int i = 0; i < 9; i++){
        if(activeDrop[i]){
          numDrops--;
          strip.setPixelColor(rain[i][dropPosition[i]], strip.Color(0, 0, 127));
          if(rain[i][(dropPosition[i] + 1)] < 0){
            dropPosition[i] = 0;
            activeDrop[i] = false;
          }
          else{
            dropPosition[i]++;
          }
        }
      }
      
      if(numDrops > 0){
        for(int i = 0; i < numDrops; i++){
          int column = -1;
          while(column < 0){
            int rand = constrain((int)random(0, 9), 0, 8);
            if(!activeDrop[rand]){
              column = rand;
            }
          }
          activeDrop[column] = true;
        }
      }
    }
    //strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
  }
  
  ////INPUTS 
  
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
  wheelChange = qe.tick();
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
}

void clearRain(){
  for(int i = 0; i < 50; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}

void resetRain(){
  for(int j = 0; j < 9; j++){
    dropPosition[j] = 0;
    activeDrop[j] = false;
  }
}

void clearClouds(){
  for(int i = 50; i < 64; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}

float msToMin(float millliseconds){
  return (millliseconds / 1000.0 / 60.0); 
}

//code adapated from http://arduino.cc/forum/index.php/topic,3922.0.html 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}


