#pragma once
#include "Enemy.h"
#include"HidenObj.h"
#include "FireBall.h"
class BigBat:public Enemy
{
	int P, Direc_y;
	float backup_x, backup_y, des_x, des_y;
	float a, b, c;
	float a1, b1;
	bool IsWaiting;
	HidenObj* Des;
	Camera* cam;
	DWORD TimeWait;
	vector<FireBall*> LstFireBall;
public:
	BigBat( simon*S);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj = NULL);
	void CalRef();
	float CalY(float X);
	void CalRef1();
	float CalY1(float X);
	float CalX1(float Y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render(Camera* Cam);
	~BigBat() {}
};

