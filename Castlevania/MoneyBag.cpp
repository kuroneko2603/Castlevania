#include "MoneyBag.h"

MoneyBag::MoneyBag(int T)
{
	State = T;
	type = MONEYBAG;
	if (T == 1) {
		Score = 100;
	}
	if (T == 2) {
		Score = 400;
	}
	if (T == 3) {
		Score = 700;
	}
	if (T == 4)
	{
		Score = 1000;
	}
	Texture = CTextures::GetInstance()->GetTexture(GType::MONEYBAG);
	sprite = new CSprite(Texture);
	vy = 0.18f;
	Health = 1;
	SetSize(32, 30);
}
