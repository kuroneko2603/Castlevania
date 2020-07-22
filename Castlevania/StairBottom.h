#pragma once
#include "GameObject.h"
class StairBottom: public CGameObject
{
public:
	StairBottom()
	{
		type = GType::STAIRBOT;
		SetSize(50, 16);
		Texture = CTextures::GetInstance()->GetTexture(GType::BBOX);

	}
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL)
	{

	}
	void Render(Camera* cam) { //CGameObject::RenderBBox(cam);
	}
	~StairBottom() {}
};

