#include "FireBall.h"

FireBall::FireBall(simon* S, float X1, float Y1, float X2, float Y2)
{
	type = GType::FIREBALL;
	Texture = CTextures::GetInstance()->GetTexture(GType::FIREBALL);
	sprite = new CSprite(Texture);
	Simon = S;
	x = X1;
	y = Y1;
	if (X2 > X1) {
		Direc = -1;
		vx = 0.1f;
	}
	else {
		Direc = 1;
		vx = -0.1f;
	}
	CalRef(X1, Y1, X2, Y2);
	Health = 1;
	SetSize(16, 16);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	if (Health <= 0)
		return;
	if (abs(y - CalY(x + dt * vx)) < abs(x - (x + dt * vx)))
	{
		x += dt * vx;
		y = CalY(x);
	}
	else
	{
		y += -0.1f * dt;
		x = CalX(y);
	}
	if (isCollisionWithObj(Simon))
	{
		if (!Simon->Invisible)
			Simon->SubHealth(1);
		Simon->SetIsGetHurt(true);
		Health--;
	}
}

void FireBall::CalRef(float X1, float Y1, float X2, float Y2)
{
	a = (Y2+30-Y1) / (X2-X1);
	b = Y1 - a * X1;
}

float FireBall::CalY(float X)
{
	return a * X + b;
}

float FireBall::CalX(float Y)
{
	return (Y - b) / a;
}

FireBall::~FireBall()
{
}
