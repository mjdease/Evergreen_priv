#pragma once
#include "../ofMain.h"

class EverTexture
{
public:
	EverTexture(string src);
	EverTexture(void);
	~EverTexture(void);


	virtual void draw(float offset);
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	void draw(float x, float y, float w, float h, float rotation);
	void draw(float x, float y, float rotation);
	void drawTexture(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
	void loadTexture(string src);
	void setOpacity(float alpha);

	float getHeight();
	float getWidth();

protected:
	string src;
	ofImage image;
	ofTexture texture;
	float width;
	float height;
	float opacity;
};

