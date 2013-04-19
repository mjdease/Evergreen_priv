#pragma once
#include "ofMain.h"

class Audio
{
public:
	ofSoundPlayer audio;
	string file;

	void start(void);
	void stop(void);
	void setVol(string);
	// void setVol(float);

	Audio(string);
	~Audio(void);
};

