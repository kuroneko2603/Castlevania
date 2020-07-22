#include "Burn.h"

Burn::Burn(float X, float Y)
{
	count = 1;
	x = X;
	y = Y;
	type = GType::BURN;
	tex = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(tex);
}
