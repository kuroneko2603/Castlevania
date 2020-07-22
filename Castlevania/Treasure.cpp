#include "Treasure.h"

void Treasure::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
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
}
