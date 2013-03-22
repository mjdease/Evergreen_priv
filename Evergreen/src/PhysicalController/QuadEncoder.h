/**
 * QuadEncoder.h - Library for reading moves from a quadrature rotary encoder
 * Created by Pedro Rodrigues (medecau@gmail.com) 9, January of 2010
 * Released into the public domain.
 * Updated by Scottapotamas scott@26oclock.com for arduino 1.0 ice
 * Updated by Matt Dease for open frameworks
 */
#include "ofMain.h"

class QuadEncoder
{
  public:
	QuadEncoder();
    QuadEncoder(ofArduino* arduino, int pin1, int pin2);
    char tick();
  private:
	ofArduino* ard;
	bool _moved;
    int _inputPin1;
    int _inputPin2;
    int _val1;
    int _val2;
    int _oldVal1;
    int _oldVal2;
    int _pos;
    int _oldPos;
    int _turn;
    int _turnCount;  
};