#include "Cross.h"

Cross::Cross()
{
	TimeCreate = GetTickCount64();
	Texture = CTextures::GetInstance()->GetTexture(GType::CROSS);
	type = GType::CROSS;
	sprite = new CSprite(Texture);
	Damage = 1;
	Step = 0;
	vx = -0.2f;
	SetSize(32, 32);
	Health = 1;
}

void Cross::Attack(float X, float Y, int D)
{
	if (IsFinish == false)
		return;
	IsFinish = false;
	this->x = X;
	this->y = Y;
	Start_x = X;
	Start_y = Y;
	this->Direc = D;
	AdjustPosition();
	vx = abs(vx) * Direc;
	if (State != 2) 
	{
		State = 2;
		sprite->SetState(2);
	}
	Step = 0;
	Special = false;
	Sound::GetInstance()->Play(GSOUND::S_CROSS, false);
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	vy = 0.18f;
	if (State != 1) {
		State = 1;
		sprite->SetState(1);
	}
	DWORD now = GetTickCount64();
	CGameObject::Update(dt);
	if (now - TimeCreate>=8000)
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

void Cross::AdjustPosition()
{
	if (Direc == -1)
	{
		this->x = x;
		this->y += 10;

	}
	else
	{
		this->x = x + 30;
		this->y += 10;
	}
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coObj)
{
	x += vx * dt;
	if (IsFinish)
	{
		if (Step == 1)
			Step = 0;
		return;
	}
	if (Step == 0)
	{
		if (abs(x - Start_x) >= 250)
		{
			Step++;
			Special = true;
			vx = -vx;
		}
	}
	for (int i = 0; i < coEnemy->size(); i++)
	{
		if (coEnemy->at(i) != NULL)
			if (isCollisionWithObj(coEnemy->at(i)))
			{
				RandomItem(coEnemy->at(i));
				coEnemy->at(i)->SubHealth(Damage);
			}
	}
	for (int i = 0; i < coObj->size(); i++)
	{
		if (coObj->at(i) != NULL) {
			GType T = coObj->at(i)->GetType();
			if (T != GType::BRICK && T != GType::HIDENOBJ && T != GType::STAIRTOP && T != GType::STAIRBOT && T != GType::SECRETBRICK)
				if (isCollisionWithObj(coObj->at(i)))
				{
					RandomItem(coObj->at(i));
					coObj->at(i)->SubHealth(Damage);
					return;
				}
		}
	}
}

void Cross::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + GetW() - 10;
	bottom = top + GetH();
}
