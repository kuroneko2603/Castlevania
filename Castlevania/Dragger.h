#pragma once
#include"Weapon.h"
#define DRAGGER_SPEED 0.4f
#define DRAGGER_WIDTH 32
#define DRAGGER_HEIGHT 18
class Dragger:public Weapon
{
	DWORD TimeExist, TotalTime;
public:
	Dragger();
	~Dragger();
	void AdjustPosition();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* ListEnemy, vector<LPGAMEOBJECT>* ListObj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* ListObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetW() { return DRAGGER_WIDTH; }
	int GetH() { return DRAGGER_HEIGHT; }
};

