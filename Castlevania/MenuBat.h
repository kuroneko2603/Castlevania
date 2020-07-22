#pragma once
#include"GameObject.h"
class MenuBat:public CGameObject
{
public:
	MenuBat() {
		Texture = CTextures::GetInstance()->GetTexture(GType::MENUBAT);
		sprite = new CSprite(Texture);
	};
	void Render(Camera* cam)
	{
		sprite->Draw(349, 129, -1);
	}
	~MenuBat() {};
};

