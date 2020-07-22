#include "Crown.h"

void Crown::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	{
		CGameObject::Update(dt);
		TotalTime += dt;
		if (TotalTime >= TimeExist)
		{
			SubHealth(1);
			return;
		}
		if (TotalTime >= 1700)
			State = 2;
		if (!IsFinish())
		{
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			CalcPotentialCollisions(coObj, coEvents);
			if (coEvents.size() == 0)
			{
				//y += dy;
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
	}
}
