#pragma once
#include "Enemy.h"
class Bat:public Enemy
{

	int Step;
	DWORD WaitTime;
public:
	Bat( simon * S);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	void Reborn(int S = 0)
	{
		Health = 1;
		vx = 0;
		vy = 0;
		Activate = false;
		Step = 0;
		State = 1;
	}
	~Bat() {}
};

