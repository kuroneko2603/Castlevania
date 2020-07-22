#pragma once
#include "Sprites.h"
#include "Camera.h"
class Effect
{
protected:
	CTexture* tex;
	CSprite* sprite;
	bool IsFinish;
	float x, y;
	GType type;
public:
	Effect();
	~Effect()
	{
		SAFE_DELETE(sprite);
	}
	virtual void Render(Camera* cam);
	virtual void Update(DWORD dt);
	bool getFinish() { return IsFinish; }
};

