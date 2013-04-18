#pragma once
#include "../Draw/EverTexture.h"
class EverCloud :public EverTexture
{
public:
	EverTexture* cloud;

	float speed;
	float posy;
	float posx;

	void draw();

	EverCloud(void);
	~EverCloud(void);
};

