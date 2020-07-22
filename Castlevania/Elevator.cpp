#include "Elevator.h"

Elevator::Elevator()
{
	type = GType::ELEVATOR;
	Texture = CTextures::GetInstance()->GetTexture(GType::ELEVATOR);
	sprite = new CSprite(Texture);
	vy = 0;
	vx = 0.05f;
	SetSize(64, 16);
}

void Elevator::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	if(vx>0 && (x- Start_x>=64))
		vx=-0.05f;
	if (vx < 0 && (x < Start_x + 5))
		vx = 0.05f;
	x += vx * dt;
}
