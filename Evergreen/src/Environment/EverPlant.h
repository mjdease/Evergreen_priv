#pragma once
#include "../ofMain.h"
#include "../Draw/EverTexture.h"
#include "../DisplayManager.h"

class EverPlant
{
public:
	bool deleteMe;

	EverPlant(ofPoint position, bool thorn);
	void erase();
	void draw();
	~EverPlant(void);

private:
	bool thorn;
	static EverTexture* thornTexture;
	static EverTexture* flowerTexture;
	ofPoint position;
	ofPoint MAX_SIZE;
	float plantWidth, plantHeight;
};

