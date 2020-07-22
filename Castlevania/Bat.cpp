#include "Bat.h"

Bat::Bat( simon *S)
{
	Simon = S;
	type = GType::BAT;
	Texture = CTextures::GetInstance()->GetTexture(GType::BAT);
	sprite = new CSprite(Texture);
	Health = 1;
	vx = 0;
	vy = 0; 
	SetSize(32, 32);
	Activate = false;
	RangeLeft = RangeRight = 200;
	Step = 0;
	State = 1;
	Score = 100;
	sprite->SetState(1);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	DWORD now = GetTickCount64();
	if ((abs(Simon->GetX() - x) <= RangeLeft) && !Activate && (abs(Simon->GetY()- y)<=100))
	{
		//DebugOut(L"%f %f\n", x, y);
		State = 2;
		sprite->SetState(2);
		Activate = true;
		WaitTime = now;
		if (Simon->GetX() < x)
		{
			Direc = -1;
		}
		else
			Direc = 1;
	}
	if (Activate)
	{
		vy = 0.1f;
		vx = Direc*0.06f;
		if (Step == 0)
		{
			if (now - WaitTime >= 500)
			{
				Step++;
				WaitTime = now;
			}
		}
		if (Step == 1)
		{
			vx = 0; vy = 0;
			if (now - WaitTime >= 100)
			{
				Step++;
				WaitTime = now;
			}
		}
		if (Step == 2)
		{
			vy = 0;
			vx = Direc * 0.151f;
		}
	}
	x += vx * dt;
	y += vy * dt;
	float l1, l2, b1, b2, r1, r2, t1, t2;
	this->GetBoundingBox(l1, t1, r1, b1);
	Simon->GetBoundingBox(l2, t2, r2, b2);
	if (CGame::GetInstance()->CheckAABB(l1 + 5, t1 + 5, r1, b1, l2, t2, r2, b2))
	{
		Health--;
	}
}
