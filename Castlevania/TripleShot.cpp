#include "TripleShot.h"

TripleShot::TripleShot()
{
	type = GType::TRIPLESHOT;
	Texture = CTextures::GetInstance()->GetTexture(GType::TRIPLESHOT);
	sprite = new CSprite(Texture);
	vy = 0.2f;
	vx = 0;
	SetSize(32, 32);
	Health = 1;
}
