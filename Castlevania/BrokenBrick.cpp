#include "BrokenBrick.h"

BrokenBrick::BrokenBrick(float X, float Y)
{
	type = GType::BRICKEFCT;
	tex = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(tex);
	sprite2 = new CSprite(CTextures::GetInstance()->GetTexture(type));
	sprite3 = new CSprite(tex);
	sprite4 = new CSprite(tex);
	x=x2=x3=x4 = X;
	y=y2=y3=y4 = Y;
	vx = 0.15f;
	vx2 = -0.15f;
	vx3 = 0.07;
	vx4 = -0.1f;
	vy = -0.25f;
	vy2 = -0.25f;
	vy3 = -0.22f;
	vy4 = -0.3f;
}

void BrokenBrick::Render(Camera* cam)
{
	if (!IsFinish)
	{
		D3DXVECTOR3 p = cam->PossInCamera(x, y);
		D3DXVECTOR3 p2 = cam->PossInCamera(x2, y2);
		D3DXVECTOR3 p3 = cam->PossInCamera(x3, y3);
		D3DXVECTOR3 p4 = cam->PossInCamera(x4, y4);

		sprite->Draw(p.x, p.y, -1);
		sprite2->Draw(p2.x, p2.y, -1);
		sprite3->Draw(p3.x, p3.y, -1);
		sprite4->Draw(p4.x, p4.y, -1);
	}
}

void BrokenBrick::Update(DWORD dt)
{
	vy += 0.002f * dt;
	vy2 += 0.002f * dt;
	vy3 += 0.002f * dt;
	vy4 += 0.002f * dt;
	x += dt * vx;
	x2 += dt * vx2;
	x3+= dt * vx3;
	x4 += dt * vx4;
	y += dt * vy;
	y2 += dt * vy2;
	y3 += dt * vy3;
	y4 += dt * vy4;
	if (y >= 500)
	{
		IsFinish = true;
	}
}
