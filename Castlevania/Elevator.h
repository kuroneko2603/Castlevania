#pragma once
#include "GameObject.h"
class Elevator: public CGameObject
{
public :
	Elevator();
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL);
	~Elevator() {}
};

