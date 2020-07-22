#pragma once
#include "Weapon.h"
class ThrowingAxe:public Weapon
{
	DWORD TimeCreate;
public:
	ThrowingAxe();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	void Attack(float X, float Y, int D);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = this->x;
		top = this->y;
		right = left + GetW() - 10;
		bottom = top + GetH();
	}
	~ThrowingAxe() {};
};

