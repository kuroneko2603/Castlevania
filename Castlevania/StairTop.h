#pragma once
#include "GameObject.h"
class StairTop:public CGameObject
{
public:
	StairTop()
	{
		type = GType::STAIRTOP;
		SetSize(50, 16);
		Texture = CTextures::GetInstance()->GetTexture(GType::BBOX);
	}
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL)
	{

	}
	void Render(Camera* cam) { CGameObject::RenderBBox(cam); }
	~StairTop(){}
};

