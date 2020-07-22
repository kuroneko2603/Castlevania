#pragma once
#include"GameObject.h"
class IntroBat:public CGameObject
{
public:
	IntroBat(int dt);
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL)
	{
		x += Direc * 0.005 * dt;
		if (Direc == 1)
			y += 0.001 * dt;
	}
	~IntroBat();
};

