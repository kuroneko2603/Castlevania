#include "Raven.h"

Raven::Raven(simon *S)
{
	vx = vy = 0;
	Texture = CTextures::GetInstance()->GetTexture(GType::RAVEN);
	type = GType::RAVEN;
	sprite = new CSprite(Texture);
	RangeLeft = RangeRight = 150;
	Activate = false;
	IsAttacking = false;
	AutoGo_X = AutoGo_Y = 0;
	Simon = S;
	Step = 0;
	Score = 150;
	HitTime = WaitTime = 0;
	IsCalSpeed = false;
	SetSize(32, 32);
	nWait = 0;
	nHit = 0;
	nFlyUp = 0;
	IsFlyUp = false;
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	DWORD now = GetTickCount64();
	if (Simon->GetX() <= x + RangeRight && Simon->GetX() >= x - RangeLeft && abs(y- Simon->GetY())<=300)
	{
		if (!Activate)
		{
			Activate = true;
			Distance_Y = (abs(y - Simon->GetY()));
			Backup_y = y;
			State = 2;
			sprite->SetState(2);
		}
	}
	if (Activate)
	{
		if (Simon->GetX() > x)
			Direc = 1;
		if (Simon->GetX() < x)
			Direc = -1;
		if (Simon->GetY() > y)
			Direc_y = 1;
		else
			Direc_y = -1;
		if (Step == 0)
		{
			vx = Direc * 0.1f;
			vy = Direc_y * 0.1f;
			if (abs(y - Backup_y >= (Distance_Y * 0.5f)))
			{
				Step++;
				WaitTime = now;
			}
		}
		if (Step == 1)
		{
			vx = 0; 
			vy = 0;
			if (now - WaitTime >= 300)
				Step++;
		}
		if (Step == 2)
		{
			if (!IsCalSpeed)
			{
				if (!IsFlyUp)
				{
					Des_y = Simon->GetY();
					Des_x = Simon->GetX();
				}
				
				if (Des_x < x)
					Direc = -1;
				if (Des_x > x)
					Direc = 1;
				if (Des_y < y)
					Direc_y = -1;
				else
					Direc_y = 1;
				float tmp = abs(Des_y - y) * 10;
				vx = Direc * (abs(Des_x - x) - 20) / (tmp);
				if (abs(vx) > 0.2f)
					vx = 0.18f * Direc;
				vy = Direc_y * 0.1f;
				if ((y + 10 > Des_y && Direc_y==1) || (y < (Des_y + Simon->GetH()) && Direc_y==-1))
				{
					vx = Direc * 0.18f;
					vy = 0;
				}
				IsCalSpeed = true;
			}
			float l1, l2, b1, b2, r1, r2, t1, t2;
			this->GetBoundingBox(l1, t1, r1, b1);
			Simon->GetBoundingBox(l2, t2, r2, b2);
			if (CGame::GetInstance()->CheckAABB(l1 + 5, t1 + 5, r1 - 10, b1 - 10, Des_x, Des_y, Des_x+32, Des_y+80))
			{
				if (IsFlyUp)
					IsFlyUp = false;
				if (CGame::GetInstance()->CheckAABB(l1 + 5, t1 + 5, r1 - 10, b1 - 10, l2, t2, r2, b2))
				{
					Step++;
					WaitTime = now;
					nWait = 0;
					//Health--;
					if (now - HitTime >= 3000)
					{
						HitTime = now;
						nHit++;
					}
				}
				else
				{
					Step--;
					IsCalSpeed = false;
					if (nWait == 0)
					{
						WaitTime = now;
						nWait++;
					}
				}
			}
		}
		if (Step == 3)
		{
			vx = 0; 
			vy = 0;
			if (now - WaitTime >= 700)
			{
				if(Simon->GetX()>x)
					Des_x = x +  80;
				if (Simon->GetX() < x)
					Des_x = x - 80;
				Des_y = Simon->GetY();
				if (nHit < 3)
				{
					Step--;
					srand(time(NULL));
					int iFly = rand() % 10 + 1;
					if (iFly >= 7 && nFlyUp<2)
					{
						IsFlyUp = true;
						Des_x = -Direc * 80 + x;
						Des_y = y - 100;
						IsCalSpeed = false;
						nFlyUp++;
					}
				}
				else
					Step++;
				vx = Direc * 0.19f;
				nWait = 0;
				//WaitTime = now;
			}
		}

	}
	x += vx * dt;
	y += vy * dt;
}

void Raven::Render(Camera* cam)
{
	CGameObject::Render(cam);
}

