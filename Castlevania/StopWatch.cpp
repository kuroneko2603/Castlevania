#include "StopWatch.h"

StopWatch::StopWatch()
{
	TimeCreate = GetTickCount64();
	type = GType::STOPWATCH;
	Texture = CTextures::GetInstance()->GetTexture(GType::STOPWATCH);
	sprite = new CSprite(Texture);
	Health = 1;
	SetSize(32, 32);
}

void StopWatch::Attack(float X, float Y, int D)
{
}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
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

void StopWatch::AdjustPosition()
{
}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj)
{
}

void StopWatch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + GetW() - 10;
	bottom = top + GetH();
}
