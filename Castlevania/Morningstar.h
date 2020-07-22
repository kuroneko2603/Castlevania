#pragma once
#include "GameObject.h"
#include"Weapon.h"
#include "Sound.h"
class Morningstar:public Weapon
{
public:
	Morningstar();
	~Morningstar() {}
	void Attack(float X, float Y, int D);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* ListEnemy, vector<LPGAMEOBJECT>* ListObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RandomItem(LPGAMEOBJECT Obj);
	void Upgrade() { if (lv < 2) lv++; 	sprite->SetState(lv+1);}
	void Render(Camera* cam);
	GType GetType() { return type; }
};

