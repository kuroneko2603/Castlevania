#pragma once
#include "Simon.h"
#include "Enemy.h"
class Knight:public Enemy	
{
	bool IsWaiting;
	int Status;
public:
	Knight(simon *S);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	~Knight() {};
};

