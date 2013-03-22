/**
 * QuadEncoder.cpp - Library for reading moves from a quadrature rotary encoder
 * Created by Pedro Rodrigues (medecau@gmail.com) 9, January of 2010
 * Modified by Andreas Lekas (spadusa@gmail.com) 31, January, 2010
 * Released into the public domain.
 * Updated by Scottapotamas scott@26oclock.com for arduino 1.0 ice
 * Updated by Matt Dease for open frameworks
 */

#include "QuadEncoder.h"

QuadEncoder::QuadEncoder(){

}

QuadEncoder::QuadEncoder(ofArduino ard, int pin1, int pin2)
{
	QuadEncoder::ard = ard;
	QuadEncoder::ard.sendDigitalPinMode(pin1, ARD_INPUT);
	QuadEncoder::ard.sendDigitalPinMode(pin2, ARD_INPUT);
	QuadEncoder::ard.sendDigital(pin1, ARD_HIGH);
	QuadEncoder::ard.sendDigital(pin2, ARD_HIGH);
	_inputPin1=pin1;
	_inputPin2=pin2;
	_val1=1;
	_val2=1;
	_oldVal1=1;
	_oldVal2=1;
	_pos=0;
	_oldPos=0;
	_turn=0;
	_turnCount=0;
}

char QuadEncoder::tick()
{  
  _moved = false;
  _val1 = ard.getDigital(_inputPin1);
  _val2 = ard.getDigital(_inputPin2);
    // Detect changes
  if ( _val1 != _oldVal1 || _val2 != _oldVal2) {
    _oldVal1=_val1;
    _oldVal2=_val2;
    
      //for each pair there's a position out of four
    if ( _val1 == 1 ) {// stationary position
      if (_val2 == 1)
        _pos = 0;
      else if (_val2 == 0)
        _pos = 3;
    } else if (_val1 == 0){
      if (_val2 == 1)
        _pos = 1;
      else if (_val2 == 0)
        _pos = 2;
    }
    
    _turn = _pos-_oldPos;
    _oldPos = _pos;
    if (abs(_turn) != 2) {
      if (_turn == 1 || _turn == -3)
        _turnCount++;
      else if (_turn == -1 || _turn == 3)
        _turnCount--;
    }
    
    if (_pos==0){
      if (_turnCount>0){
        _turnCount=0;
		_moved = true;
        return '>';
      } else if (_turnCount<0){
		_moved = true;
        _turnCount=0;
        return '<';
      } else {
		_moved = false;
        _turnCount=0;
        return '-';
      }
    }
  }
}