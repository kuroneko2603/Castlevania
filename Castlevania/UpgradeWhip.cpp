#include "UpgradeWhip.h"

UpgradeWhip::UpgradeWhip()
{
	type = GType::UPGRADEWEAPON;
	Health = 1;
	vx = 0.18f; vy = 0.2f;
	Texture = CTextures::GetInstance()->GetTexture(GType::UPGRADEWEAPON);
	SetSize(28, UWHIP_HEIGHT);
	sprite = new CSprite(Texture);
}

