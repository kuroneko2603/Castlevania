#pragma once
#include "Simon.h"
#include "Enemy.h"

class Fleaman:public Enemy 
{
	int Step;
	bool checkBrick, AtkSimon, HitBrick, Ready;
	bool IsReturn;
	bool Esc;
	DWORD ReadyTime, TimeAtk, TimeHitBrick;
	int nHit;
public:
	Fleaman(simon *S);
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObject = NULL);
	float CalSpeed();
	void Render(Camera* cam);
	void Reborn(int S = 0);
	~Fleaman();
};

