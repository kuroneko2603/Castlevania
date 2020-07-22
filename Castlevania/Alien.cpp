#include "Alien.h"

Alien::Alien(simon* S)
{
	Simon = S;
	type = GType::ALIEN;
	Texture = CTextures::GetInstance()->GetTexture(GType::ALIEN);
	sprite = new CSprite(Texture);
	Health= Backup_health = 2;
	Step = 0;
	Activate = false;
	SetSize(32, 32);
	RangeLeft = RangeRight = 200;
	Score = 200;
	vx = 0;
	vy = 0;
}

void Alien::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (abs(x - Simon->GetX()) < RangeLeft && Step==0)
	{
		Step++;
	}
	if (Step == 1 && abs(y - Simon->GetY())<=200 && abs(x- Simon->GetX())>=200)
	{
		Step++;
		Activate = true;
	}
	if (Step == 2)
	{
		if (Simon->GetY() > y + 32)
			vy = 0.05f;
		if (Simon->GetY() + Simon->GetH() < y)
			vy = -0.05f;
		if (y<Simon->GetY() + Simon->GetH() && y>Simon->GetY())
			vy = 0;
		if (Simon->GetX() < x)
			Direc = -1;
		else
			Direc = 1;
		vx = Direc * 0.08f;
		float l1, l2, b1, b2, r1, r2, t1, t2;
		this->GetBoundingBox(l1, t1, r1, b1);
		Simon->GetBoundingBox(l2, t2, r2, b2);
		if (CGame::GetInstance()->CheckAABB(l1 + 20, t1, r1 - 10, b1, l2, t2, r2, b2))
		{
			vx = 0;
		}
	}
	if (Health < Backup_health)
	{
		Backup_health = Health;
		IsGetHit = false;
	}
	x += vx * dt;
	y += vy * dt;
}

void Alien::Render(Camera* cam)
{
	if (Activate)
		CGameObject::Render(cam);
}

