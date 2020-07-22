#pragma once
#include "GameObject.h"
class HidenObj:public CGameObject
{
	int Width, Height;
	float Bonus_x, Bonus_y;
	int Bonus_type;
	int Stage;
public:
	HidenObj(int Simon_X, int Simon_Y, int d,int stage=1, int hObj=0);
	~HidenObj() {}
	float Simon_x, Simon_y;
	void SetSize(int W, int H);
	int GetStage() { return Stage; }
	void GetBonusInfo(float& Bx, float& By, int& Btype) { Bx = Simon_x; By = Simon_y; Btype = Stage; }
	void GetSimonPosition(float& Simon_X, float& Simon_Y, int& Simon_Direc) { Simon_X = Simon_x; Simon_Y = Simon_y; Simon_Direc = Direc; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>*ListObj= NULL);
	void Render(Camera* cam);
};

