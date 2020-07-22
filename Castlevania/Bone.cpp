#include "Bone.h"

Bone::Bone(simon* S, float VX, float VY, float X, float Y)
{
	type = BONE;
	Texture = CTextures::GetInstance()->GetTexture(GType::BONE);
	sprite = new CSprite(Texture);
	Simon = S;
	vx = VX;
	vy = -VY;
	x = X;
	y = Y;
	Health = 1;
	Tupdate = 0;
	Backup_y = y;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	if (Health == 0)
		return;
	Tupdate++;
	x += vx * dt;
	y += vy * dt;
	vy += 0.001f * dt;
	//DebugOut(L"vy %f %f %f\n", vy, y, Backup_y);
	if (isCollisionWithObj(Simon))
	{
		if(!Simon->Invisible)
			Simon->SubHealth(1);
		Simon->SetIsGetHurt(true);
		Health--;
	}
	if (y >= 500)
	{
		Health--;
	}
}
