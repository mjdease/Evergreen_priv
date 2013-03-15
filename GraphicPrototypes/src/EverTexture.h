#pragma once
#include "ofMain.h"

class EverTexture
{
public:
	EverTexture(string src);
	~EverTexture(void);

	void setImage(string src);

	virtual void draw(float height);
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	void draw(float x, float y, float w, float h, float rotation);
	void draw(float x, float y, float rotation);

private:
	string src;
	ofImage image;
};

