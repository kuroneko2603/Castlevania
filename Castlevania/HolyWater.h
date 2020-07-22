#pragma once
#include "Weapon.h"
class HolyWater:public Weapon
{
	DWORD TimeCreate, TimeBurn;
public:
	HolyWater();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	void Attack(float X, float Y, int D);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj);
	~HolyWater() {}
};

