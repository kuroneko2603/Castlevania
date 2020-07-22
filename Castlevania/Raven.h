#pragma once
#include "Enemy.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
class Raven:public Enemy
{
	float AutoGo_Y, AutoGo_X;
	float Distance_X, Distance_Y;
	bool IsCalSpeed;
	bool IsFlyUp;
	float Des_x, Des_y;
	int nWait, nHit, nFlyUp;
	int Step;
	DWORD WaitTime, HitTime;
	int Direc_y;
public:
	Raven(simon *S);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	~Raven() {};
	void Render(Camera* cam);
};

