#pragma once
#include "EverTexture.h"
class EverCloud :
	public EverTexture
{
public:
	EverTexture* cloud;
	
	float spd;
	float posy;
	float posx;

	void draw();

	EverCloud(void);
	~EverCloud(void);
};

