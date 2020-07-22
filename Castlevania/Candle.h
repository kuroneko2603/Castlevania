#pragma once
#include "GameObject.h"
class Candle:public CGameObject
{
public:
	Candle()
	{
		Health = 1;
		Texture = CTextures::GetInstance()->GetTexture(GType::CANDLE);
		SetSize(32, 16);
		sprite = new CSprite(Texture);
		type = GType::CANDLE;
		vx = 0;
		vy = 0;
	}
	~Candle() {}
	int GetW() { return  16; }
	int GetH() { return  32; }
};

