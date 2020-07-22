#include "Item.h"

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
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
		CalcPotentialCollisions(coObj, coEvents); // Lấy danh sách các va chạm 
		// No collision occured, proceed normally
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
}
