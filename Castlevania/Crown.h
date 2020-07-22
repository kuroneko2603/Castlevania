#pragma once
#include"Item.h"
class Crown:public Item
{
public:
	Crown() {
		Sound::GetInstance()->Play(GSOUND::DISPLAYTREASURE, false);
		type = GType::CROWN;
		Texture = CTextures::GetInstance()->GetTexture(type);
		sprite = new CSprite(Texture);
		SetSize(32, 32);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	void Render(Camera* cam)
	{
		if (sprite->GetState() != State)
			sprite->SetState(State);
		sprite->Draw(x, y, -1);
	}
	~Crown() {};
};

