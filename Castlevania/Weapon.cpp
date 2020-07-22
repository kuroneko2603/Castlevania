#include "Weapon.h"

Weapon::Weapon()
{
	IsFinish = true;
	Direc = 1;
	Damage = 1;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	Special = false;
	HitTime = 0;
}

void Weapon::AdjustPosition()
{
	if (Direc == -1)
	{
		this->x = x - 75;
		this->y = y;
	}
	else
	{
		this->x = x - 25;
		this->y = y;
	}
}

void Weapon::Attack(float X, float Y, int D)
{
	if (IsFinish == false)
		return;
	IsFinish = false;
	this->x = X;
	this->y = Y;
	Start_x = X;
	Start_y = Y;
	this->Direc = D;
	AdjustPosition();
	vx = abs(vx) * Direc;
	sprite->SetState(1);
	Sound::GetInstance()->Play(GSOUND::S_CROSS, false);
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* ListEnemy, vector <LPGAMEOBJECT>* ListObj)
{
	if (IsFinish)
		return;
	x += vx * dt;
	y += vy * dt;
	for (int i = 0; i < ListEnemy->size(); i++)
	{
		if (ListEnemy->at(i) != NULL)
			if (isCollisionWithObj(ListEnemy->at(i)))
			{
				ListEnemy->at(i)->SubHealth(Damage);
				IsFinish = true;
				return;
			}
	}
	for (int i = 0; i < ListObj->size(); i++)
	{
		if (ListObj->at(i) != NULL)
			if (ListObj->at(i)->GetType() != GType::BRICK)
				if (isCollisionWithObj(ListObj->at(i)))
				{
					ListObj->at(i)->SubHealth(Damage);
					IsFinish = true;
					return;
				}
	}
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + GetW() - 10;
	bottom = top + GetH();
}

void Weapon::Render(Camera* cam)
{
	if (sprite->GetState() != State) {
		sprite->SetState(State);
	}
	if (!ObjIsInCamera(cam))
	{
		IsFinish = true;
		return;
	}
	float BR, BL, BT, BB;
	cam->GetBoundary(BL, BR, BT, BB);
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	this->sprite->Draw(xCam, yCam, Direc);
}

void Weapon::RandomItem(LPGAMEOBJECT Obj)
{
	if (Obj->GetHiden() != 0)
		return;
	if (type == GType::MORNINGSTAR)
		return;
	HitTime++;
	if (HitTime == 10)
		Obj->SetHiden(GType::DOUBLESHOT);
	if (HitTime == 20)
		Obj->SetHiden(GType::TRIPLESHOT);
	if (Obj->GetHiden() != 0)
		return;
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
}
