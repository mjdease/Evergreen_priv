#pragma once
#include "ofMain.h"

class EverTexture
{
public:
	EverTexture(string src);
	~EverTexture(void);

	void setImage(string src);

	virtual void draw(float offset);
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	void draw(float x, float y, float w, float h, float rotation);
	void draw(float x, float y, float rotation);

protected:
	string src;
	ofImage image;
	float width;
	float height;
};

