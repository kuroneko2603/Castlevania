#pragma once
#include "Simon.h"
class FireBall:public CGameObject
{
	simon* Simon;
	float a, b;
public:
	FireBall(simon* S, float X1, float Y1, float X2, float Y2);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	void CalRef(float X1, float Y1, float X2, float Y2);
	float CalY(float X);
	float CalX(float Y);
	~FireBall();
};

