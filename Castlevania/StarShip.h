#pragma once
#include"GameObject.h"
class StarShip:public CGameObject
{
public:
	StarShip() {
		sprite = new CSprite(CTextures::GetInstance()->GetTexture(GType::STARSHIP));
	};
	void Update(DWORD dt);
	~StarShip() { };
};

