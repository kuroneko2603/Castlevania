#include "HidenObj.h"

HidenObj::HidenObj(int Simon_X,int Simon_Y, int d, int stage, int hObj)
{
	SetSize(16, 16);
	Stage = stage;
	Simon_x = Simon_X*1.0f;
	Simon_y = Simon_Y*1.0f;
	Direc = d;
	type = GType::HIDENOBJ;
}

void HidenObj::SetSize(int W, int H)
{
	Width = W;
	Height = H;
}

void HidenObj::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + Width;
	bottom = y + Height;
}

void HidenObj::Update(DWORD dt, vector<LPGAMEOBJECT> *ListObj)
{

}

void HidenObj::Render(Camera* cam)
{
	CGameObject::RenderBBox(cam);
}
