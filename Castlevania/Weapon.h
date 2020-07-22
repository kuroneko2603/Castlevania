#pragma once
#include"GameObject.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Sound.h"
class Weapon:public CGameObject
{
protected:
	int Damage;
	bool IsFinish;
	int lv;
	DWORD TimeAtk;
	int HitTime;
public:
	Weapon();
	~Weapon() {}
	bool Special;
	virtual void Upgrade() {};
	virtual void AdjustPosition();
	virtual void Render(Camera* cam);
	virtual void SetLv(int LV) { lv = LV; }
	virtual void RandomItem(LPGAMEOBJECT Obj);
	virtual int GetDame() { return Damage; };
	virtual void SetHitTime(int HT) { HitTime = HT; }
	void SetDirec(int D) { Direc = D; return; }
	virtual void Attack(float X, float Y, int D);
	virtual bool GetIsFinish() { return IsFinish; }
	virtual void SetFinish(bool B) { IsFinish = B; return; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> * ListEnemy, vector<LPGAMEOBJECT> *ListObj);
};

