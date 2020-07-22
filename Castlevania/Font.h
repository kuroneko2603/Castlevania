#pragma once
#include "Sprites.h"
class Font
{
	CSprite* sprite;
public:
	Font();
	void Render(float x, float y, string str, int Type = 1);
	~Font();
};

