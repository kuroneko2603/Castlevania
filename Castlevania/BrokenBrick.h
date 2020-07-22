#pragma once
#include"Effect.h"
class BrokenBrick:public Effect
{
	float x2, x3, x4, y2, y3, y4;
	float vx, vy, vx2, vy2, vx3, vy3,vx4, vy4;
	CSprite* sprite2;
	CSprite* sprite3;
	CSprite* sprite4;
public:
	BrokenBrick(float X, float Y);
	virtual void Render(Camera* cam);
	virtual void Update(DWORD dt);
	~BrokenBrick() {}
};

