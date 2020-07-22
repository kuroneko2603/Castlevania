#include "Hit.h"

Hit::Hit(float X, float Y)
{
	x = X;
	y = Y;
	type = GType::HIT;
	tex = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(tex);
}
