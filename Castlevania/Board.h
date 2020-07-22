#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "Game.h"
#include "Simon.h"
#include "Font.h"
#define BOARD_WIDTH 520
#define BOARD_HEIGHT 80
class Board
{
	CTexture* texture;
	CTexture* texF;
	CTexture* texH;
	CTexture* texS;
	CSprite* Sprite;
	CSprite* SpriteH;
	CSprite* SpriteF;
	CTexture* fonttexture;
	CSprite* fontsprite;
	CTexture* texDShot;
	CSprite* SpriteDShot;
	Font* font;
	CGameObject* boss;
	float x, y;
public:
	Board();
	void SetBoss(CGameObject* B) { boss = B; }
	~Board() { SAFE_DELETE(Sprite); }
	void Render(simon* Simon,int Time , int stage);
};

