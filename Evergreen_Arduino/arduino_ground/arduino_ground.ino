//RFID code is based off examples found at http://playground.arduino.cc/Learning/PRFID

#include <SoftwareSerial.h>

#define PLANT "p:"
#define SHAKE "k:"

#define GRASS_ID "01068DE864"
#define FLOWER_ID "01068DD85B"
#define THORN_ID "01068DDA1E"

#define EMPTY_VAL 0
#define GRASS_VAL 1
#define FLOWER_VAL 2
#define THORN_VAL 3

//increase the threshold as the interval decreases
#define RFID_INTERVAL 100
#define EMPTY_RFID_THRESHOLD 6

#define ACC_PIN A0
#define ACC_INTERVAL 300


// RFID reader SOUT pin connected to Arduino pin8, nothing on pin 9.
SoftwareSerial RFID = SoftwareSerial(8, 9); 

unsigned long pRfidTime = 0;
unsigned long pAccTime = 0;

int currentPlant = EMPTY_VAL;
int emptyCount = 0;
int pAcc;
int accDiff = 0;

void setup(){ 
  Serial.begin(115200);  // Hardware serial for Monitor 2400bps

  pinMode(2,OUTPUT);       // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  digitalWrite(2, LOW);    // Activate the RFID reader 
  
  RFID.begin(2400);
  
  pAcc = analogRead(ACC_PIN);
}


void loop(){ 
  unsigned long time = millis();
  
  int accelerometer = analogRead(ACC_PIN);
  int diff = abs(accelerometer - pAcc);
  if(diff > 10){
    accDiff += diff;
  }
  pAcc = accelerometer;
  
  if(time - pAccTime > ACC_INTERVAL){
    if(accDiff > 35){
      Serial.print(SHAKE);
      //value typically ranges from 0 - 150
      Serial.println(accDiff);
    }
    accDiff = 0;
    pAccTime = time;
  }
  
  if(time - pRfidTime > RFID_INTERVAL){
    int val = 0;
    int bytesread = 0;
    char code[11]; 
    
    pRfidTime = time;

    if(RFID.available()){
      // check for header 
      if((val = RFID.read()) == 10){
        //read 10 digit code
        while(bytesread < 10){  
          val = RFID.read(); 
          // if header or stop bytes before the 10 digit reading stop reading 
          if((val == 10)||(val == 13)){
            break;
          } 
          code[bytesread] = val;     
          bytesread++;
        }
        clearSerial();
    
        if(bytesread == 10){
          code[bytesread] = '\0';
          emptyCount = 0;
          if(currentPlant != GRASS_VAL && strcmp(GRASS_ID, code) == 0){
            currentPlant = GRASS_VAL;
            Serial.print(PLANT);
            Serial.println(GRASS_VAL);
          }
          else if(currentPlant != FLOWER_VAL && strcmp(FLOWER_ID, code) == 0){
            currentPlant = FLOWER_VAL;
            Serial.print(PLANT);
            Serial.println(FLOWER_VAL);
          }
          else if(currentPlant != THORN_VAL && strcmp(THORN_ID, code) == 0){
            currentPlant = THORN_VAL;
            Serial.print(PLANT);
            Serial.println(THORN_VAL);
          }
        }
      } 
      else{//serial data not recognized
        clearSerial();
        //Serial.println("not recognized");
      }
    }
    else{//no serial data
      emptyCount++;
      if(currentPlant != EMPTY_VAL && emptyCount > EMPTY_RFID_THRESHOLD){
        emptyCount = 0;
        currentPlant = EMPTY_VAL;
        Serial.print(PLANT);
        Serial.println(EMPTY_VAL);
      }
    }
  }
  delay(10);
} 

void clearSerial(){
  //clear any remaining data
  while(RFID.available()){
    RFID.read();
  }
}
