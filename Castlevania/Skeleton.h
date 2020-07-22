#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Bone.h"
#include <cstdlib>
#include <ctime>
class Skeleton:public Enemy
{
	vector<Bone*> LstBone;
	bool IsAutoGo;
	int AutoGoDistance;
	DWORD LastTimeAtk;
	int RTime;
public:
	Skeleton(simon*S);
	void Attack();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Camera * cam);
	float CalvxForBone();
	void SetHealth(int H)
	{
		DebugOut(L"Deheo\n");
		if (LstBone.size()==0)
			return;
		Health = H;
	}
	void Reborn(int  s = 0);
	~Skeleton();
};

