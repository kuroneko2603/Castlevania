#include "Brick.h"

Brick::Brick(int W, int H)
{
	Width = W;
	Height = H;
	type = GType::BRICK;
	x = 0; y = 330;
}

void Brick::Render(Camera* cam)
{
	//CGameObject::RenderBBox(cam);
}

void Brick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + Width;
	bottom = y +Height;
}
