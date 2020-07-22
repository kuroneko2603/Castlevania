#include "InvisibilityPotion.h"

InvisibilityPotion::InvisibilityPotion()
{
	type = GType::IPOTION;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	Health = 1;
	SetSize(32, 30);
	vy = 0.18f;
}
