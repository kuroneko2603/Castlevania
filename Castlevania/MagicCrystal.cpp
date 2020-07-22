#include "MagicCrystal.h"

MagicCrystal::MagicCrystal()
{
	type = GType::MAGICCRYSTAL;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	SetSize(32, 32);
	Health = 1;
	vy = 0.4f;
}
