#include "Rosary.h"

Rosary::Rosary()
{
	type = GType::ROSARY;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	SetSize(32, 32);
	Health = 1;
	vy = 0.18f;
}
