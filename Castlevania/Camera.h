#pragma once
#include"define.h"
class Camera
{
	float x, y, Backup_x, vx, Backup_y;
	float BLeft, BRight, BTop, BBottom;
	bool IsFollowSimon, IsAutoGoX;
	float AutoGoDistance;
public:
	bool ReachDes;
	Camera() 
	{
		ReachDes = false;
		AutoGoDistance = 0;
		Backup_x = Backup_y = 0;
		BLeft = BRight = BTop = BBottom = 0;
		x = y = 0;
		IsFollowSimon = true;
		vx = 0;
		Backup_x = 0;
		IsAutoGoX = false;
	}
	~Camera();
	void GetBoundary(float& BL, float& BR, float& BT, float& BB) { BL = BLeft; BR = BRight; BT = BTop; BB = BBottom; }
	void SetBoundary(float BL, float BR, float BT, float BB) { BLeft = BL; BRight = BR; BTop = BT; BBottom = BB; }
	
	void GetPosition(float& X, float& Y) { X = x; Y = y; }
	void SetPosition(float X, float Y) { x = X; y = Y; }
	float GetX() { return x; }
	float GetY() { return y; }
	void RestorePosition() { x = Backup_x; y = Backup_y; }

	bool GetIsFollowSimon() { return IsFollowSimon; }
	void SetIsFollowSimon(bool fl) { IsFollowSimon = fl; }

	void AutoGoStart(float d)
	{ 
		ReachDes = false;
		if (IsAutoGoX)
			return;
		Backup_x = x;
		IsAutoGoX = true; 
		vx = 0.1f; 
		IsFollowSimon = false;
		AutoGoDistance = d;
	}
	void Update(DWORD dt);
	D3DXVECTOR3 PossInCamera(float xMap, float yMap) { return D3DXVECTOR3(trunc(xMap - x), trunc(yMap - y), 0); }
};

