#pragma once
#include "../Draw/EverTexture.h"
class EverCloud :public EverTexture
{
public:
	EverTexture* cloud;
	
	float spd;
	float posy;
	float posx;

	void draw(float offset);

	EverCloud(void);
	~EverCloud(void);
};

