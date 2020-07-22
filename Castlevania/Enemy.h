#pragma once
#include "GameObject.h"
#include "Simon.h"
#define ENEMY_GRAVITY_JUMP 0.001f
#define ENEMY_GRAVITY 0.005f
#define ENEMY_JUMP_SPEED 0.32f
#define ENEMY_SPEED 0.12f
class Enemy :public CGameObject
{
protected:
	simon* Simon;
	DWORD TimeGetHit;
	int RangeLeft, RangeRight;
	bool IsAttacking, IsJumping;
	float Backup_x, Backup_y;
public:
	Enemy();
	void SetPosition(float X, float Y) { this->x = X, this->y = Y; Backup_x = x; Backup_y = y; Start_x = x; Start_y = y; }
	void SubHealth(int Dame) {
		DWORD now = GetTickCount64(); 
		if (now - TimeGetHit > 300) 
		{ 
			Health -= Dame; 
			TimeGetHit = now; 
			IsGetHit = true; 
		}
		if (Health == 0)
			TdeActivate = now;
	}
	~Enemy();
};

