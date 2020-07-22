#pragma once
#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64
#include"GameObject.h"
class Torch:public CGameObject
{
public:
	Torch()
	{
		Health = 1;
		Texture = CTextures::GetInstance()->GetTexture(GType::TORCH);
		SetSize(TORCH_WIDTH, TORCH_HEIGHT);
		sprite = new CSprite(Texture);
		type = GType::TORCH;
		vx = 0;
		vy = 0;
	}
	~Torch() {}
	int GetW() { return TORCH_WIDTH; }
	int GetH() { return  TORCH_HEIGHT; }
};

