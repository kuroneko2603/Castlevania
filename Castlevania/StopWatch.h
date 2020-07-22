#pragma once
#include "Weapon.h"
class StopWatch: public Weapon
{
	int Step;
	DWORD TimeCreate;
public:
	StopWatch();
	void Attack(float X, float Y, int D);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	void AdjustPosition();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	~StopWatch() {}
};

