#include "Morningstar.h"

Morningstar::Morningstar()
{
	IsFinish = true;
	Direc = 1;
	lv = 0;
	Damage = 1;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	this->Texture = CTextures::GetInstance()->GetTexture(GType::MORNINGSTAR);
	SetSize(160, 68);
	this->sprite = new CSprite(Texture);
}

void Morningstar::Attack(float X, float Y, int D)
{
	if (IsFinish == false)
		return;
	IsFinish = false;
	this->x = X;
	this->y = Y;
	this->Direc = D;
	vx = abs(vx) * Direc;
	sprite->SetState(lv + 1);
	Sound::GetInstance()->Play(GSOUND::S_WHIP, false);
}

void Morningstar::Update(DWORD dt, vector<LPGAMEOBJECT>* ListEnemy, vector<LPGAMEOBJECT>* ListObj)
{
	if (IsFinish)
	{
		return;
	}
	for (int i = 0; i < ListEnemy->size(); i++)
	{
		if (ListEnemy->at(i) != NULL)
			if (isCollisionWithObj(ListEnemy->at(i))) {
				RandomItem(ListEnemy->at(i));
				ListEnemy->at(i)->SubHealth(Damage);
			}
	}
	for (int i = 0; i < ListObj->size(); i++)
	{
		if (ListObj->at(i) != NULL && ListObj->at(i)->GetType() != GType::HIDENOBJ && ListObj->at(i)->GetType() != GType::STAIRTOP && ListObj->at(i)->GetType() != GType::STAIRBOT)
			if (ListObj->at(i)->GetType() != GType::BRICK)
				if (isCollisionWithObj(ListObj->at(i)))
				{
					RandomItem(ListObj->at(i));
					ListObj->at(i)->SubHealth(Damage);
					if (ListObj->at(i)->GetType() == GType::SECRETBRICK)
						Sound::GetInstance()->Play(GSOUND::BROKENBRICK, false);
				}
	}
}

void Morningstar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (sprite->GetmapId() == 2)
	{
		switch (lv)
		{
		case 0:
		{
			if (Direc == 1)
			{
				left = x + 75;
				top = y + 15;
				right = x + GetW() - 34;
				bottom = y + GetH() - 10;
			}
			else
			{
				left = x + 30;
				top = y + 15;
				right = x + GetW() - 78;
				bottom = y + GetH() - 23;

			}
			break;
		}
		case 1:
		{
			if (Direc == 1)
			{
				left = x + 78;
				top = y + 15;
				right = x + GetW() - 30;
				bottom = y + GetH() - 23;
			}
			else
			{
				left = x + 30;
				top = y + 15;
				right = x + GetW() - 80;
				bottom = y + GetH() - 23;

			}
			break;
		}
		case 2:
		{
			if (Direc == 1)
			{
				left = x + 78;
				top = y + 15;
				right = x + GetW();
				bottom = y + GetH() - 23;
			}
			else
			{
				left = x;
				top = y + 15;
				right = x + GetW() - 80;
				bottom = y + GetH() - 23;

			}
			break;
		}
		default:
			break;
		}
	}
}

void Morningstar::RandomItem(LPGAMEOBJECT Obj)
{
	if (Obj->GetHiden() != 0)
		return;
	if (lv < 2)
	{
		Obj->SetHiden(GType::UPGRADEWEAPON);
		return;
	}
	srand(time(NULL));
	int result = rand() % 100 + 1;
	if (result <= 50)
		Obj->SetHiden(GType::HEART);
	if (result >= 51 && result <= 60)
		Obj->SetHiden(GType::REDMONEYBAG);
	if (result >= 61 && result <= 70)
		Obj->SetHiden(GType::WHITEMONEYBAG);
	if (result >= 71 && result <= 80)
		Obj->SetHiden(GType::PURPLEMONEYBAG);
	if (result >= 81 && result <= 85)
		Obj->SetHiden(GType::MONEYBAG);
	if (result >= 86 && result <= 94)
		Obj->SetHiden(GType::IPOTION);
	if (result >= 95)
		Obj->SetHiden(GType::ROSARY);
	return;
}

void Morningstar::Render(Camera* cam)
{
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	this->sprite->Draw(xCam, yCam, Direc);
}
