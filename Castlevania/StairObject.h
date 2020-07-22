#pragma once
#include "GameObject.h"
class StairObject:public CGameObject
{
public:
	StairObject(int type, int H)
	{
		Hiden = H;
		SetSize(32, 32);
		if (type == 1)
			type = GType::STAIRTOP;
		else
			type = GType::STAIRBOT;
	}
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL) {}
	//void Render(Camera* cam) {}
	~StairObject() {}
};

