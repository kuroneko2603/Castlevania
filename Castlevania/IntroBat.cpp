#include "IntroBat.h"

IntroBat::IntroBat(int dt)
{
	type = GType::INTROBAT;
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	Direc = dt;
}

IntroBat::~IntroBat()
{
}
