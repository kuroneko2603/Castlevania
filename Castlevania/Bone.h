#pragma once
#include "GameObject.h"
#include "Simon.h"
#define GRAVITY 0.005f
class Bone:public CGameObject
{
	simon* Simon;
	int Tupdate;
	float Backup_y;
public :
	Bone(simon * S, float VX, float VY, float X, float Y);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObj = NULL);
	~Bone() {};
};

