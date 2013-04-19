#pragma once
#include "../Draw/EverTexture.h"
class EverCloud
{
public:
	EverTexture* cloud;

	float speed;
	float posy;
	float posx;
	
	float sizePercent;

	void update();
	void draw();
	
	void setOpacity(float alpha);

	EverCloud(void);
	~EverCloud(void);

private:
	float width, height;
};

