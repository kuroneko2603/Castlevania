#include "Board.h"

Board::Board()
{
	y = 0;
	x = 3;
	texture = CTextures::GetInstance()->GetTexture(GType::BOARD);
	Sprite = new CSprite(texture);
	texH = CTextures::GetInstance()->GetTexture(GType::HEALTH);
	SpriteH = new CSprite(texH);
	texF = CTextures::GetInstance()->GetTexture(GType::FONT);
	SpriteF = new CSprite(texF);
	texDShot = CTextures::GetInstance()->GetTexture(GType::DOUBLESHOT);
	SpriteDShot = new CSprite(texDShot);
	font = new Font();
}

void Board::Render(simon* Simon, int Time, int stage)
{
	Sprite->DrawBoard(x, y);
	int i;
	int SimonHealth = Simon->GetHealth();
	int SimonHeartCollect = Simon->GetHeart();
	for (i = 0; i < SimonHealth; i++)
	{
		SpriteH->SelectFrame(1);
		SpriteH->DrawBoard(x + 110.0f + i * 11.0f, y + 32.0f);
	}
	for (i = SimonHealth; i < 16; i++)
	{
		SpriteH->SelectFrame(2);
		SpriteH->DrawBoard(x + 110 + (i) * 11, y + 32);
	}
	if (boss == NULL)
		for (int j = 0; j < 16; j++)
		{
			SpriteH->SelectFrame(3);
			SpriteH->DrawBoard(x + 110 + j * 11, y + 52);
		}
	else
	{
		for (int j = 0; j < boss->GetHealth(); j++)
		{
			SpriteH->SelectFrame(3);
			SpriteH->DrawBoard(x + 110 + j * 11, y + 52);
		}
		for (int j = boss->GetHealth(); j < 16; j++)
		{
			SpriteH->SelectFrame(2);
			SpriteH->DrawBoard(x + 110 + (j) * 11, y + 52);
		}
	}
	//so luong tim dg giu
	int heart = Simon->GetHeart();
	string Strheart = to_string(heart);
	if (Strheart.length() < 2)
		Strheart = "0" + Strheart;
	for (int k = 0; k < Strheart.length(); k++)
	{
		int num = (int)(Strheart[k]) - 21;//-48+27
		SpriteF->SelectFrame(num);
		SpriteF->DrawBoard(x + 395 + (k) * 15, y + 34);
	}
	//diem hien tai
	int score = Simon->GetScore();
	string Strscore = to_string(score);
	if (Strscore.length() == 1)
		Strscore = "00000" + Strscore;
	if (Strscore.length() == 2)
		Strscore = "0000" + Strscore;
	if (Strscore.length() == 3)
		Strscore = "000" + Strscore;
	if (Strscore.length() == 4)
		Strscore = "00" + Strscore;
	if (Strscore.length() == 5)
		Strscore = "0" + Strscore;
	for (int k = 0; k < 6; k++)
	{
		int num = (int)(Strscore[k]) - 21;//-48+27
		SpriteF->SelectFrame(num);
		SpriteF->DrawBoard(x + 111 + (k) * 15, y + 15);
	}
	//thoi gian con lai 
	string Strtime = "0" + to_string(Time);
	font->Render(x + 290, y + 15, Strtime);
	//thong tin stage
	string StrStage = "0" + to_string(stage);
	font->Render(x + 465, y + 15, StrStage);
	//tong tin lives simon
	string StrHeart = "0" + to_string(Simon->Getlive());
	font->Render(x + 395, y + 53, StrHeart);
	//ve vu khi phu
	if (Simon->GetSubWeapon_Obj() != NULL)
	{
		Simon->GetSubWeapon_Obj()->GetSprite()->DrawItem(x + 310.0f, y + 32.0f);
	}
	if (Simon->GetDoubleShot)
	{
		SpriteDShot->DrawBoard(x + 445, y + 35);
	}
}
