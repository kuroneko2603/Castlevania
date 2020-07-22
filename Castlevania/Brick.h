#pragma once
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 64
#include "GameObject.h"
class Brick:public CGameObject
{
	int Width, Height;
public:
	Brick(int W, int H);
	~Brick() {}
	int GetW() { return Width; }
	int GetH() { return Height; }
	void Render(Camera* cam);
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObj = NULL)
	{

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void Render();
};

