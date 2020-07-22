#include "DoubleShot.h"

DoubleShot::DoubleShot()
{
	type = GType::DOUBLESHOT;
	Texture = CTextures::GetInstance()->GetTexture(GType::DOUBLESHOT);
	sprite = new CSprite(Texture);
	Health = 1;
	vx = 0;
	SetSize(32, 32);
	vy = 0.18f;
}
