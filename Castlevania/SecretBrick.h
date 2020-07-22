#pragma once
#include "GameObject.h"
class SecretBrick:public CGameObject
{
public :
	SecretBrick(float X, float Y, int Sg) {
		x = X;
		y = Y;
		State = Sg;
		type = GType::SECRETBRICK;
		Texture = CTextures::GetInstance()->GetTexture(type);
		sprite = new CSprite(Texture);
		SetSize(32, 32);
	}
	void Render(Camera* cam) {
		D3DXVECTOR3 p=cam->PossInCamera(x, y);
		if (sprite->GetState() != State)
			sprite->SetState(State);
		sprite->Draw(p.x, p.y, -1);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = left + 32;
		bottom = top + 32;
	}
	~SecretBrick() {}
};

