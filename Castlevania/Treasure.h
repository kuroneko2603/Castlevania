#pragma once
#include "Item.h"
class Treasure:public Item
{
public:
	Treasure() {
		type = GType::TREASURE;
		Texture = CTextures::GetInstance()->GetTexture(type);
		sprite = new CSprite(Texture);
		Sound::GetInstance()->Play(GSOUND::DISPLAYTREASURE, false);
		SetSize(32, 32);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	void Render(Camera* cam)
	{
		D3DXVECTOR3 p = cam->PossInCamera(x, y);
		if (sprite->GetState() != State)
		{
			sprite->SetState(State);
		}
		sprite->Draw(p.x, p.y, -1);
	}
	~Treasure() {}
};

