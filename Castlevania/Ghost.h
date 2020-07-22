#pragma once
#define	GHOST_WIDTH 34
#define GHOST_HEIGHT 64
#include "Enemy.h"
#include "Camera.h"
class Ghost:public Enemy
{
	Camera* cam;
	float BLeft, BRight;
	float alpha;
public:
	Ghost(int A= 0);
	~Ghost();
	int GetHealth() { return Health; }
	int GetDamage() { return Damage; }
	int GetW() { return GHOST_WIDTH; }
	int GetH() { return GHOST_HEIGHT; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render(Camera* Cam)
	{
		if (Health<=0)
			return;
		cam = Cam;
		if (sprite->GetState() != State)
		{
			sprite->SetState(State);
		}
		float xCam = cam->PossInCamera(x, y).x;
		float yCam = cam->PossInCamera(x, y).y;
		if (Health >= 1)
			this->sprite->Draw(xCam, yCam, Direc);
		//RenderBBox(Cam);
	}
	void Reborn(int S=0) 
	{
		//DebugOut(L"%d\n", GetTickCount64() - TdeActivate);
		if (GetTickCount64() - TdeActivate < 2000)
			return;
		Direc = -1 * Direc;
		if (Direc == 1)
		{
			x = cam->GetX() + 40;
			vx = 0.12f;
		}
		else 
		{
			x = cam->GetX() + 470;
			int t = rand() % 10;
			if (t > 7)
				y = 150;
			else
				y = 260;
			vx = -0.12f;
		}
		Activate = true;
		Health = 1;
	}
};
