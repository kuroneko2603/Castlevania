#include "HolyWater.h"

HolyWater::HolyWater()
{
	type = GType::HOLYWATER;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	Health = 1;
	SetSize(32, 32);
	TimeCreate = GetTickCount64();
	State = 1;
	Damage = 1;
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	vy += 0.18f;
	DWORD now = GetTickCount64();
	CGameObject::Update(dt);
	if (now - TimeCreate >= 8000)
	{
		SubHealth(1);
		return;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObj, coEvents);
	if (coEvents.size() == 0)
	{
		//DebugOut(L"no col\n");
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void HolyWater::Attack(float X, float Y, int D)
{
	if (!IsFinish)
		return;
	IsFinish = false;
	this->x = X;
	this->y = Y;
	Start_x = X;
	State = 1;
	Start_y = Y;
	this->Direc = D;
	vx = 0.15f * Direc;
	vy = -0.35f;
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj)
{
	DebugOut(L"Holy w\n");
	DWORD now = GetTickCount64();
	x += vx * dt;
	vy += 0.001f * dt;
	if (State == 2)
	{
		vx = vy = 0;
	}
	y += vy * dt;
	if (State == 2 && now - TimeBurn >= 2000)
		IsFinish = true;
	if (IsFinish)
	{
		return;
	}
	for (int i = 0; i < coEnemy->size(); i++)
	{
		if (coEnemy->at(i) != NULL)
			if (isCollisionWithObj(coEnemy->at(i)))
			{
				coEnemy->at(i)->SubHealth(Damage);
			}
	}
	for (int i = 0; i < coObj->size(); i++)
	{
		DebugOut(L"Col obj\n");
		if (coObj->at(i) != NULL) 
		{
			GType T = coObj->at(i)->GetType();
			if (T != GType::BRICK && T != GType::HIDENOBJ && T != GType::STAIRTOP && T != GType::STAIRBOT && T != GType::SECRETBRICK)
				if (isCollisionWithObj(coObj->at(i)))
				{
					coObj->at(i)->SubHealth(Damage);
					return;
				}
			if (T== GType::BRICK && isCollisionWithObj(coObj->at(i)) && y <= coObj->at(i)->GetY() && State != 2)
			{
				State = 2;
				TimeBurn = now;
			}
		}
		else
		{

		}

	}
}
