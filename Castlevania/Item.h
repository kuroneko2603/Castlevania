#pragma once
#include "GameObject.h"
#include "Simon.h"
class Item:public CGameObject
{
protected:
	DWORD TimeExist, TotalTime;

public :
	Item()
	{
		vy = 0.1f;
		TotalTime = 0;
		Health = 1;
		TimeExist = 8000;
	}
	~Item(){}
	int GetTimeExist() { return TimeExist; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = this->x+15;
		top = this->y;
		right = left + GetW();
		bottom = top + GetH();
	}
	bool IsFinish() { return (TotalTime > TimeExist|| Health==0); }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>*coObj);
};

