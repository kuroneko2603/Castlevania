#include "Font.h"

Font::Font()
{
	sprite = new CSprite(CTextures::GetInstance()->GetTexture(GType::FONT));
}

void Font::Render(float x, float y, string str, int Type)
{
	for (int i = 0; i < str.length(); i++)
	{
		int num;
		if (str[i] >= '0' && str[i] <= '9')
			num = (int)(str[i]) - 21;//-48+27
			else
				if (str[i] >= 'a' && str[i] <= 'z')
					num = (int)(str[i]) - 96;//-97+1
				else
					num = 38;
		sprite->SelectFrame(num);
		if(num!=38)
			sprite->DrawBoard(x + (i) * 15, y);
	}
}

Font::~Font()
{
	SAFE_DELETE(sprite);
}
