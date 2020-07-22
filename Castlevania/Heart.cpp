#include "Heart.h"

Heart::Heart(int S)
{
	size = S;
	if (size == 1)
	{
		Texture = CTextures::GetInstance()->GetTexture(GType::HEART);
		SetSize(HEART_WIDTH, HEART_HEIGHT);
		type = GType::HEART;
	}
	else
	{
		Texture = CTextures::GetInstance()->GetTexture(GType::BIGHEART);
		SetSize(BIGHEART_WIDTH, BIGHEART_HEIGHT);
		type = GType::BIGHEART;
	}
	sprite = new CSprite(Texture);
	x = 0; y = 0; vx = 0; vy = 0.12f; Direc = 1;
	if(size==1)
	vx = 0.08f;
}

int Heart::GetW()
{
	if (size == 1)
		return HEART_WIDTH;
	else
		return BIGHEART_WIDTH;
}

int Heart::GetH()
{
	if (size == 1)
		return HEART_HEIGHT;
	else
		return BIGHEART_HEIGHT;
}

void Heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	CGameObject::Update(dt);
	TotalTime += dt;
	if (TotalTime >= TimeExist)
	{
		SubHealth(1);
		return;
	}
	if (!IsFinish())
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		CalcPotentialCollisions(coObj, coEvents);
		
		if (coEvents.size() == 0)
		{
			if (size == 1 && abs(x - Start_x) >= 30)
			{
				vx = -1 * vx;
				Start_x = x;
			}
			x += dt * vx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;
			x += min_tx * dx + nx * 0.4f;
			if (nx!= 0)
			{
				if (size == 1)
					x += vx * dt;
			}
			if (ny != 0 && nx == 0)
			{
				DebugOut(L"No\n");
				vy = 0;
				vx = 0;
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}
