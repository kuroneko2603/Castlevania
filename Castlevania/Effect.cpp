#include "Effect.h"

Effect::Effect()
{
	x = y = 0;
	IsFinish = false;
}

void Effect::Render(Camera* cam)
{
	if (!IsFinish)
	{
		D3DXVECTOR3 p = cam->PossInCamera(x, y);
		sprite->Draw(p.x, p.y,-1);
	}
}
void Effect::Update(DWORD dt)
{
	if (IsFinish)
		return;
	IsFinish = sprite->IsFinish;
	return;
}
