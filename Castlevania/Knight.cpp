#include "Knight.h"

Knight::Knight(simon* S)
{
	Simon = S;
	Health = Backup_health = 2;
	Texture = CTextures::GetInstance()->GetTexture(GType::KNIGHT);
	type = GType::KNIGHT;
	sprite = new CSprite(Texture);
	RangeLeft = 100;
	RangeRight = 100;
	IsWaiting = false;
	IsAttacking = false;
	Score = 200;
	vx = 0.09f;
	vy = 0;
	SetSize(32, 64);
	Status = 0;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	DWORD now = GetTickCount64();
	if ((x - Start_x)>=60)
	{
		Direc = -1;
		vx = -0.09f;
	}
	if (x - Start_x <= -60)
	{
		Direc = 1;
		vx = 0.09f;
	}
	if (Health < Backup_health)
		IsGetHit = false;
	CGameObject::Update(dt);
	vy += 0.01f * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObj, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			vx *= -1;
			Direc *= -1;
		}
		if (ny != 0)
			vy = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
