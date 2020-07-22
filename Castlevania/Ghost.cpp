#include "Ghost.h"


Ghost::Ghost(int A)
{
	alpha = A;
	Direc = 1;
	vx = 0.12f;
	vy = 0;
	type = GType::GHOST;
	Health = 1;
	Damage = 1;
	BRight = 500;
	alpha = 30;
	Activate = true;
	BLeft = 0;
	Texture = CTextures::GetInstance()->GetTexture(GType::GHOST);
	SetSize(GHOST_WIDTH, GHOST_HEIGHT);
	sprite = new CSprite(Texture);
	Score = 100;
}

Ghost::~Ghost()
{
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	DebugOut(L"%f\n", x);
	DWORD now = GetTickCount64();
	if (Health <= 0)
		return;
	if (Direc == 1)
		vx = 0.12f;
	else
		vx = -0.12f;
	if (cam != NULL)
	{
		BLeft = cam->GetX();
		BRight = BLeft + SCREEN_WIDTH - 40;
	}
	if (cam!= NULL && (x- cam->GetX()) > 550)
	{
		DeadByOutcam = true;
		TdeActivate = now;
		Health = 0;
	}
	if (x < BLeft)
	{
		DeadByOutcam = true;
		TdeActivate = now;
		Health = 0;
	}
	CGameObject::Update(dt);
	vy += 0.01f * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObj->size(); i++)
		if (coObj->at(i) != NULL)
			if (coObj->at(i)->GetType() == GType::BRICK)
				listObject_Brick.push_back(coObj->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents);
	/*if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else*/
	{
		//
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0)
		{
		}
		x += dt*vx;
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0)
			vy = 0;

	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	DebugOut(L"%f %d\n", x, Health);
}

void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x+5;
	top = y;
	right = x + 32-5;
	bottom = y + 64;
}


