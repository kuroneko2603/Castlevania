#pragma once
#include "Weapon.h"
class Cross :public Weapon
{
	int Step;
	DWORD TimeCreate;
public:
	Cross();
	void Attack(float X, float Y, int D);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	void AdjustPosition();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	~Cross() {}
};

