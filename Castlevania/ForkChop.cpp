#include "ForkChop.h"

ForkChop::ForkChop()
{
	type = GType::FORKCHOP;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	SetSize(32, 30);
	Health = 1;
	vy = 0.18f;
}
